#pragma once

#include "stone/AST.hpp"
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
			m_depth++;
			printTab();
			m_os << ";" << endl;
			m_depth--;
		}
		void visit(DefFuncStmtAST *ast) {
			printTab();
			m_os << "def " << ast->funcName();
			m_os << " (";
			for (uint i = 0; i < ast->params()->size(); i++) {
				if (i)
					m_os << ", ";
				m_os << ast->params()->at(i)->name();
				if (ast->params()->at(i)->value()) {
					m_os << " = ";
					ast->params()->at(i)->value()->accept(this);
				}
			}
			m_os << ")" << endl;
			ast->funcBody()->accept(this);
		}
		void visit(IfStmtAST *ast) {
			printTab();
			m_os << "if ";
			m_os << "(";
			if (ast->condition())
				ast->condition()->accept(this);
			m_os << ")" << endl;
			if (ast->trueStmt()) {
				ast->trueStmt()->accept(this);
			} else {
				m_depth++;
				printTab();
				m_depth--;
				m_os << ";";
			}
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
		void visit(WhileStmtAST *ast) {
			printTab();
			m_os << "while ";
			m_os << "(";
			ast->condition()->accept(this);
			m_os << ")" << endl;
			printTab();
			m_os << "{" << endl;
			m_depth++;
			ast->trueStmt()->accept(this);
			m_depth--;
			printTab();
			m_os << "}" << endl;
		}
		void visit(ForStmtAST *ast) {
			printTab();
			m_os << "for ";
			m_os << "(";
			ast->init()->accept(this);
			m_os << "; ";
			ast->condition()->accept(this);
			m_os << "; ";
			ast->step()->accept(this);
			m_os << ")" << endl;
			printTab();
			ast->body()->accept(this);
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
		void visit(ExprAST *ast) {
			if (ast->postfixes()) {
				Array<PostfixAST*> *postfixes = ast->postfixes();
				for (uint i = 0; i < postfixes->size(); i++) {
					postfixes->at(i)->accept(this);
				}
			}
		}
		void visit(PostfixAST *ast) {

		}
		void visit(IndexPostfixAST *ast) {
			m_os << "[ ";
			ast->indexExpr()->accept(this);
			m_os << " ]";
		}
		void visit(MemberPostfixAST *ast) {
			m_os << ".";
			m_os << ast->memberName();
			m_os << "";
		}
		void visit(CallFuncPostfixAST *ast) {
			m_os << "(";
			for (uint i = 0; i < ast->params()->size(); i++) {
				if (i) {
					m_os << ", ";
				}
				ast->params()->at(i)->accept(this);
			}
			m_os << ")";
		}
		void visit(ExprStmtAST *ast) {
			printTab();
			ast->expr()->accept(this);
			m_os << ";" << endl;
		}
		void visit(PrintStmtAST *ast) {
			printTab();
			m_os << "print ";
			ast->expr()->accept(this);
			m_os << ";" << endl;
		}
		void visit(BinaryOpAST *ast) {
			m_os << "(";
			ast->left()->accept(this);
			m_os << " " << ast->op()->string() << " ";
			ast->right()->accept(this);
			m_os << ")";
			ast->ExprAST::accept(this);
		}
		void visit(IntLiteralAST *ast) {
			m_os << ast->value();
			ast->ExprAST::accept(this);
		}
		void visit(UnaryOpAST *ast) {
			m_os << "(";
			m_os << ast->op()->string() << " ";
			ast->operand()->accept(this);
			m_os << ")";
			ast->ExprAST::accept(this);
		}
		void visit(VarAST *ast) {
			m_os << ast->varName();
			ast->ExprAST::accept(this);
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
