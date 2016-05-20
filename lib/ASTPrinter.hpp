#pragma once

#include "AST.hpp"
#include <iostream>

namespace stone {
	using namespace std;
	class ASTPrinter : public ASTVisitor {
	public:
		ASTPrinter(ostream &os_) : m_os(os_), m_depth(0) {
		}
		void visit(AST *) {

		}
		void visit(StmtAST *ast) {

		}
		void visit(IfStmtAST *ast) {
			printTab();
			m_os << "if ";
			m_os << "(";
			if (ast->condition())
				ast->condition()->accept(this);
			m_os << ")" << endl;
			ast->trueStmt()->accept(this);
			if (ast->elseStmt()) {
				printTab();
				m_os << "else " << endl;
				{
					printTab();
					m_os << "{" << endl;
					m_depth++;
					ast->elseStmt()->accept(this);
					m_depth--;
					printTab();
					m_os << "}" << endl;
				}
			} else m_os << endl;
		}
		void visit(BlockAST *ast) {
			printTab();
			m_os << "{" << endl;
			{
				m_depth++;
				for (uint i = 0; i < ast->size(); i++) {
					//printTab();
					if (ast->at(i)) {
						if (dynamic_cast<ExprAST*>(ast->at(i)))
							printTab();
						ast->at(i)->accept(this);
					} else {
						printTab();
						m_os << "Empty Statement";
					}
					//m_os << endl;
				}
				m_depth--;
			}
			printTab();
			m_os << "}" << endl;
		}
		void visit(ExprAST *) {

		}
		void visit(ExprStmtAST *ast) {
			printTab();
			ast->expr()->accept(this);
			m_os << ";" << endl;
		}
		void visit(BinaryOpAST *ast) {
			m_os << "(";
			ast->left()->accept(this);
			m_os << " " << ast->op()->string() << " ";
			ast->right()->accept(this);
			m_os << ")";
		}
		void visit(IntLiteralAST *ast) {
			m_os << ast->value();
		}
		void visit(UnaryOpAST *ast) {
			m_os << "(";
			m_os << ast->op()->string() << " ";
			ast->operand()->accept(this);
			m_os << ")";
		}
		void visit(VarAST *ast) {
			m_os << ast->varName();
		}
	private:
		void printTab() {
			for (uint i = 0; i < m_depth; i++)
				m_os << "    ";
		}
		uint m_depth;
		ostream &m_os;
	};
}
