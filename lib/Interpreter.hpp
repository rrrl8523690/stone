#pragma once

#include "Env.hpp"
#include "AST.hpp"
#include "Token.hpp"
#include "Map.hpp"
#include "MapEnv.hpp"
#include "common.h"
#include "Message.hpp"
#include <memory>


namespace stone {
	class Interpreter : virtual public ASTVisitor {
	public:
		using EnvPtr = std::shared_ptr<Env>;
		using DataPtr = std::shared_ptr<std::shared_ptr<Data> >;
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
			if (isTrue(m_returnedData)) {
				ast->trueStmt()->accept(this);
			} else {
				ast->elseStmt()->accept(this);
			}
		}
		void visit(WhileStmtAST *ast) { // currently only supports integer conditions 
			while (true) {
				ast->condition()->accept(this);
				if (!isTrue(m_returnedData))
					break;
				ast->trueStmt()->accept(this);
			}
		}
		void visit(BlockAST *ast) {
			for (uint i = 0; i < ast->size(); i++)
				ast->at(i)->accept(this);
		}
		void visit(DefFuncStmtAST *ast) {
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
					<< static_cast<IntData*>(m_returnedData->get())->value()
					<< std::endl;
			} else {
				error("Cannot print, type error");
			}
		}
		void visit(BinaryOpAST *ast) {
			DataPtr lhs, rhs;

			m_mayCreate = (ast->op()->type() == Operator::ASSIGN);
			ast->left()->accept(this);
			lhs = m_returnedData;

			// short circuit calculation 
			Operator::OpType opType = ast->op()->type();
			if (opType == Operator::ANDALSO || opType == Operator::ORELSE) {
				switch (opType) {
				case Operator::ANDALSO:
					if (!toInt(m_returnedData)) {
						m_returnedData = toDataPtr(new IntData(false));
						return;
					}
					goto dft;
				case Operator::ORELSE:
					if (toInt(m_returnedData)) {
						m_returnedData = toDataPtr(new IntData(true));
						return;
					}
				default:
					dft:
						m_mayCreate = false;
						ast->right()->accept(this);
						m_returnedData = toDataPtr(new IntData(!!toInt(m_returnedData)));
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
					int left = static_cast<IntData*>(lhs->get())->value();
					int right = static_cast<IntData*>(rhs->get())->value();
					m_returnedData = toDataPtr(new IntData(ast->op()->calculate(left, right)));
				} else {
					error("Type error when doing binary calculation.");
				}
				break;
			}
		}
		void visit(IntLiteralAST *ast) {
			m_returnedData = toDataPtr(new IntData(ast->value()));
		}
		void visit(UnaryOpAST *ast) {
			ast->operand()->accept(this);
			if (ast->op()->type() == Operator::NEGATIVE) {
				if ((*m_returnedData)->type() == Data::INT) {
					int tmp = static_cast<IntData*>(m_returnedData->get())->value();
					m_returnedData = toDataPtr(new IntData(-tmp));
				}
			}
		}
		void visit(VarAST *ast) {
			using std::cerr;
			using std::endl;
			DataPtr data;
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
		void error(const String<char_type> &msg) {
			m_msgHandler->receive(new Message(msg));
		}
		static DataPtr toDataPtr(Data *data) {
			std::shared_ptr<Data> tmp(data);
			DataPtr res(new std::shared_ptr<Data>(tmp));
			return res;
		}
		bool isTrue(const DataPtr &ptr) {
			switch (ptr->get()->type()) {
			case Data::INT:
				return toInt(ptr);
			default:
				error("condition error: type not supported");
				return false;
			}
		}
		static int toInt(const DataPtr &ptr) {
			return static_cast<IntData*>(ptr->get())->value();
		}
		EnvPtr m_env;
		bool m_mayCreate;
		DataPtr m_returnedData;
		MsgHandler *m_msgHandler;
	};
}