#pragma once

#include "ds/Map.hpp"
#include "common/Common.h"
#include "stone/Env.hpp"
#include "stone/AST.hpp"
#include "stone/Token.hpp"
#include "stone/FuncSig.hpp"
#include "stone/FuncData.hpp"
#include "stone/MapEnv.hpp"
#include "stone/Message.hpp"
#include <memory>


namespace stone {
    class Interpreter : virtual public ASTVisitor {
    public:
        using EnvPtr = std::shared_ptr<Env>;
        using DataPtr = Data::DataPtr;
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
            DataPtrPtr funcDataPtrPtr = m_env->getOrCreate(ast->funcName());
            if (!funcDataPtrPtr->get()) {
                *funcDataPtrPtr = Data::DataPtr(new FuncData(m_env));
            } else if (funcDataPtrPtr->get()->type() != Data::FUNC) { // TODO: WARNING
                warning(String<>("warning: the function ") + ast->funcName() + "overshadows another name");
            }
            Data::FuncDataPtr funcDataPtr = std::dynamic_pointer_cast<FuncData>(*funcDataPtrPtr);
            uint minCnt = 0, maxCnt = ast->params()->size();
            for (uint i = 0; i < ast->params()->size(); i++) {
                if (!ast->params()->at(i)->value())
                    minCnt++;
            }
            funcDataPtr->functions()->append(makePair(FuncSig(minCnt, maxCnt), ast));
        }

        void visit(PostfixAST *ast) {
        }

        void visit(IndexPostfixAST *ast) {
            DataPtrPtr arrayPtrPtr = m_returnedData;
            if (!(*arrayPtrPtr) || (*arrayPtrPtr)->type() != Data::ARRAY) { // TODO: ERROR
                error(ast->pos().toString() + ": it is not an array");
                return;
            }
            ast->indexExpr()->accept(this);
            DataPtrPtr indexPtrPtr = m_returnedData;
            if ((*indexPtrPtr)->type() != Data::INT) { // TODO: ERROR
                error(ast->pos().toString() + ": the index is invalid");
                return;
            }
            Data::ArrayDataPtr arrayDataPtr = Data::toArray(*arrayPtrPtr);
            int index = Data::toInt(*indexPtrPtr)->value();
            if (index < -(int) (arrayDataPtr->array()->size()) ||
                index >= (int)arrayDataPtr->array()->size()) { // TODO: ERROR
                error(ast->pos().toString() + ": the index " + String<>::number(index) + " is out of range");
                return;
            }
            if (index < 0) {
                index += arrayDataPtr->array()->size();
            }
            m_returnedData = arrayDataPtr->array()->at(index);
        }

        void visit(MemberPostfixAST *ast) {
        }

        void visit(CallFuncPostfixAST *ast) {
            DataPtrPtr funcPtrPtr = m_returnedData;
            if (!funcPtrPtr || !funcPtrPtr->get()) {
                error("the name not found");
            } else if (funcPtrPtr->get()->type() != Data::FUNC) { // TODO: error
                std::cerr << funcPtrPtr->get()->type() << std::endl;
                error("it is not callable");
            } else { // TODO: initialize default parameters
                Data::FuncDataPtr funcDataPtr = Data::toFunc(*funcPtrPtr);
                EnvPtr outerEnv = funcDataPtr->env();
                EnvPtr parentEnv = m_env;
                EnvPtr newEnv = EnvPtr(new MapEnv(outerEnv, parentEnv));
                uint actualParamCnt = ast->params()->size();
                DefFuncStmtAST *targetFunc = nullptr;
                uint targetFuncCnt = 0;
                for (uint i = 0; i < funcDataPtr->functions()->size(); i++) {
                    if (funcDataPtr->functions()->at(i).first().match(actualParamCnt)) {
                        targetFunc = funcDataPtr->functions()->at(i).second();
                        targetFuncCnt++;
                    }
                }
                if (!targetFuncCnt) { // TODO: error
//                    std::cerr << funcDataPtr->functions()->size() << std::endl;
                    error("no valid function");
                } else if (targetFuncCnt > 1) { // TODO: error
                    std::cerr << ast->pos().line() << ", " << ast->pos().kth() << ": ";
                    error("ambiguous function call");
                    std::cerr << targetFuncCnt << std::endl;
                } else {
                    m_env = parentEnv;
                    for (uint i = 0; i < actualParamCnt; i++) {
                        DataPtrPtr dataPtrPtr = newEnv->create(targetFunc->params()->at(i)->name());
                        ast->params()->at(i)->accept(this);
                        *dataPtrPtr = *m_returnedData;
                    }
                    for (uint i = actualParamCnt; i < targetFunc->params()->size(); i++) {
                        DataPtrPtr paramPtrPtr = m_env->create(targetFunc->params()->at(i)->name());
                        targetFunc->params()->at(i)->value()->accept(this);
                        *paramPtrPtr = *m_returnedData;
                    }
                    m_env = newEnv;
                    targetFunc->funcBody()->accept(this);
                }
                m_env = m_env->parent();
            }
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

        void visit(ArrayExprAST *ast) {
            Array<ExprAST *> *exprs = ast->exprs();
            Data::ArrayDataPtr arrayPtr(new ArrayData(exprs->size()));
            for (uint i = 0; i < exprs->size(); i++) {
                exprs->at(i)->accept(this);
                arrayPtr->array()->at(i) = DataPtrPtr(new DataPtr(*m_returnedData));
            }
            m_returnedData = Data::DataPtrPtr(new DataPtr(arrayPtr));
        }

        void visit(BinaryOpAST *ast) {
            DataPtrPtr lhs, rhs;
            if (ast->op()->type() == Operator::ASSIGN) {
                m_mayCreate = false;
                ast->right()->accept(this);
                rhs = m_returnedData;
                m_mayCreate = true;
                ast->left()->accept(this);
                lhs = m_returnedData;
                *lhs = *rhs;
                m_returnedData = lhs;
                m_mayCreate = false;
            } else {
                m_mayCreate = false;
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

                if ((*lhs)->type() == Data::INT && (*rhs)->type() == Data::INT) {
                    int left = static_cast<IntData *>(lhs->get())->value();
                    int right = static_cast<IntData *>(rhs->get())->value();
                    m_returnedData = toDataPtr(new IntData(ast->op()->calculate(left, right)));
                } else {
                    error("Type error when doing binary calculation.");
                    std::cerr << (*lhs)->type() << " " << (*rhs)->type() << std::endl;
                }
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
                if (!data) { // TODO: error, name not found
                    std::cerr << ast->pos().line() << " " << ast->pos().kth() << std::endl;
                    error(ast->varName() + " name not found!");
                }
            }
            m_returnedData = data;
            if (ast->postfixes()) {
                for (uint i = 0; i < ast->postfixes()->size(); i++) {
                    ast->postfixes()->at(i)->accept(this);
                }
            }
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