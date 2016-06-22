#pragma once

#include "Env.hpp"
#include "AST.hpp"
#include "Token.hpp"
#include "Map.hpp"
#include "common.h"
#include <memory>


namespace stone {
	class Interpreter : virtual public ASTVisitor {
	public:
		using EnvPtr = std::shared_ptr<Env>;
		using DataPtr = ds::Map<String<char_type>, std::shared_ptr<Data> >::It;
		Interpreter(EnvPtr env_)
			: m_env(env_) {
		}
		void visit(AST *ast) {
		}
		void visit(StmtAST *ast) {
		}
		void visit(IfStmtAST *ast) {
		}
		void visit(WhileStmtAST *ast) {
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

		}
		void visit(BinaryOpAST *ast) {
			DataPtr lhs, rhs;
			ast->left()->accept(this);
			lhs = m_returnedData;
			ast->right()->accept(this);
			rhs = m_returnedData;

			switch (ast->op()->type()) {
			case Operator::ASSIGN:
				break;
			case Operator::ADD:
				break;
			case Operator::SUB:
				break;
			case Operator::MUL:
				break;
			case Operator::DIV:
				break;
			case Operator::EQUAL:
				break;
			}
		}
		void visit(IntLiteralAST *ast) {

		}
		void visit(UnaryOpAST *ast) {

		}
		void visit(VarAST *ast) {
			
		}
	private:
		EnvPtr m_env;
		DataPtr m_returnedData;
	};
}