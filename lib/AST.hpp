#pragma once

#include "Array.hpp" 
#include "String.hpp"

namespace stone {
	typedef typename char char_type;
	class ASTVisitor;
	class AST {
	public:
		virtual void accept(ASTVisitor *visitor) {
			//visitor->visit(this);
		}
	};
	class ExprAST : public virtual AST {

	};
	class BinaryOpAST : public virtual ExprAST {
	public:
		BinaryOpAST(ExprAST *left_, Operator *op_, ExprAST *right_) {
			m_left = left_;
			m_op = op_;
			m_right = right_;
		}
	private:
		Operator *m_op;
		ExprAST *m_left, *m_right;
	};

	class IntLiteralAST : public virtual ExprAST {
	public:
		IntLiteralAST(const String<char_type> &numString) {
			int res = 0;
			for (uint i = 0; i < numString.size(); i++) {
				res *= 10;
				res += numString[i] - '0';
			}
			m_value = res;
		}
		int value() const {
			return m_value;
		}
	private:
		int m_value;
	};

	class UnaryOpAST : public virtual ExprAST {
	public:
		UnaryOpAST(Operator *op_, ExprAST *operand_) {
			m_op = op_;
			m_operand = operand_;
		}
	private:
		Operator *m_op;
		ExprAST *m_operand;
	};

	class VarAST : public virtual ExprAST {
	public:
		VarAST(const String<char_type> &varName_) {
			m_varName = varName_;
		}
		const ds::String<char_type> &varName() const {
			return m_varName;
		}
	private:
		ds::String<char_type> m_varName;
	};

	class ASTVisitor {
	public:
		virtual void visit(AST *) = 0;
		virtual void visit(ExprAST *) = 0;
		virtual void visit(BinaryOpAST *) = 0;
		virtual void visit(IntLiteralAST *) = 0;
		virtual void visit(UnaryOpAST *) = 0;
		virtual void visit(VarAST *) = 0;
		~ASTVisitor() {
		}
	private:
	};
}