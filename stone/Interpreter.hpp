#pragma once

#include "stone/Env.hpp"
#include "stone/AST.hpp"
#include "stone/Token.hpp"
#include "ds/Map.hpp"
#include "stone/MapEnv.hpp"
#include "common/Common.h"
#include "stone/Message.hpp"
#include <memory>


namespace stone {
    class Interpreter : virtual public ASTVisitor {
    public:
        using EnvPtr = std::shared_ptr<Env>;
        using DataPtrPtr = Data::DataPtrPtr;

        Interpreter(EnvPtr env_ = EnvPtr(new MapEnv(nullptr, nullptr)))
                : m_env(env_), m_msgHandler(new MsgPrinter(std::cerr)) {
            m_mayCreate = false;
            m_returnedData = nullptr;
        }

        ~Interpreter() {
            delete m_msgHandler;
        }

        void visit(AST *ast) {
        }

        void visit(StmtAST *ast) {
        }

        void visit(IfStmtAST *ast) {
            ast->condition()->accept(this);
            if (Data::isTrue(*m_returnedData)) {
                ast->trueStmt()->accept(this);
            } else {
                ast->elseStmt()->accept(this);
            }
        }

        void visit(WhileStmtAST *ast) { // currently only supports integer conditions
            while (ast->condition()->accept(this), Data::isTrue(*m_returnedData)) {
                ast->trueStmt()->accept(this);
            }
        }

        void visit(ForStmtAST *ast) {
            if (ast->init())
                ast->init()->accept(this);
            while (true) {
                if (ast->condition() && (ast->condition()->accept(this), !Data::isTrue(*m_returnedData)))
                    return;
                ast->body()->accept(this);
                if (ast->step())
                    ast->step()->accept(this);
            }
        }

        void visit(BlockAST *ast) {
            for (uint i = 0; i < ast->size(); i++)
                ast->at(i)->accept(this);
        }

        void visit(DefFuncStmtAST *ast) {
            DataPtrPtr funcData = m_env->getOrCreate(ast->funcName());
            if (!funcData->get()) {
                *funcData = Data::DataPtr(new FuncData());
            } else if (funcData->get()->type() != Data::FUNC) { // TODO: WARNING
                warning(String<>("warning: the function ") + ast->funcName() + "overshadows another name");
            }

        }

        void visit(PostfixAST *ast) {
        }

        void visit(IndexPostfixAST *ast) {
        }

        void visit(MemberPostfixAST *ast) {
        }

        void visit(CallFuncPostfixAST *ast) {

        }

        void visit(ExprAST *ast) {

        }

        void visit(ExprStmtAST *ast) {
            ast->expr()->accept(this);
        }

        void visit(PrintStmtAST *ast) {
            ast->expr()->accept(this);
            if (m_returnedData->get()->type() == Data::INT) {
                std::cout << "STONE OUTPUT: "
                          << static_cast<IntData *>(m_returnedData->get())->value()
                          << std::endl;
            } else {
                error("Cannot print, type error");
            }
        }

        void visit(BinaryOpAST *ast) {
            DataPtrPtr lhs, rhs;

            m_mayCreate = (ast->op()->type() == Operator::ASSIGN);
            ast->left()->accept(this);
            lhs = m_returnedData;

            // short circuit calculation
            Operator::OpType opType = ast->op()->type();
            if (opType == Operator::ANDALSO || opType == Operator::ORELSE) {
                switch (opType) {
                    case Operator::ANDALSO:
                        if (!Data::toInt(*m_returnedData)->value()) {
                            m_returnedData = (new IntData(false))->toDataPtrPtr();
                            return;
                        }
                        goto dft;
                    case Operator::ORELSE:
                        if (Data::toInt(*m_returnedData)) {
                            m_returnedData = (new IntData(true))->toDataPtrPtr();
                            return;
                        }
                    default:
                    dft:
                        m_mayCreate = false;
                        ast->right()->accept(this);
                        m_returnedData = (new IntData(!!Data::toInt(*m_returnedData)))->toDataPtrPtr();
                        return;
                }
            }

            m_mayCreate = false;
            ast->right()->accept(this);
            rhs = m_returnedData;

            switch (opType) {
                case Operator::ASSIGN:
                    *lhs = *rhs;
                    m_returnedData = lhs;
                    break;
                default:
                    if ((*lhs)->type() == Data::INT && (*rhs)->type() == Data::INT) {
                        int left = static_cast<IntData *>(lhs->get())->value();
                        int right = static_cast<IntData *>(rhs->get())->value();
                        m_returnedData = toDataPtr(new IntData(ast->op()->calculate(left, right)));
                    } else {
                        error("Type error when doing binary calculation.");
                    }
                    break;
            }
        }

        void visit(IntLiteralAST *ast) {
            m_returnedData = (new IntData(ast->value()))->toDataPtrPtr();
        }

        void visit(UnaryOpAST *ast) {
            ast->operand()->accept(this);
            if (ast->op()->type() == Operator::NEGATIVE) {
                if ((*m_returnedData)->type() == Data::INT) {
                    int tmp = static_cast<IntData *>(m_returnedData->get())->value();
                    m_returnedData = (new IntData(-tmp))->toDataPtrPtr();
                }
            }
        }

        void visit(VarAST *ast) {
            using std::cerr;
            using std::endl;
            DataPtrPtr data;
            if (m_mayCreate) {
                data = m_env->getOrCreate(ast->varName());
            } else {
                data = m_env->get(ast->varName());
            }
            if (ast->postfixes()) {
                for (uint i = 0; i < ast->postfixes()->size(); i++) {
                    ast->postfixes()->at(i)->accept(this);
                }
            }
            m_returnedData = data;
        }

    private:
        // TODO: complete different types of messages
        void error(const String<char_type> &msg) {
            m_msgHandler->receive(new Message(msg));
        }

        void warning(const String<char_type> &msg) {
            m_msgHandler->receive(new Message(msg));
        }

        static DataPtrPtr toDataPtr(Data *data) {
            std::shared_ptr<Data> tmp(data);
            DataPtrPtr res(new std::shared_ptr<Data>(tmp));
            return res;
        }


        EnvPtr m_env;
        bool m_mayCreate;
        DataPtrPtr m_returnedData;
        MsgHandler *m_msgHandler;
    };
}