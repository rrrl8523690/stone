#pragma once

#include "Array.hpp" 
#include "String.hpp"

namespace stone {
	typedef typename char char_type;

	class ASTVisitor;
	class ExprAST;
	class AST {
	public:
		virtual void accept(ASTVisitor *visitor);
		virtual ~AST() {
		}
	};

	class StmtAST : public virtual AST {
	public:
		void accept(ASTVisitor *visitor);
		~StmtAST() {
		}
	};

	class IfStmtAST : public virtual StmtAST {
	public:
		IfStmtAST(ExprAST *condition_, StmtAST *trueStmt_, StmtAST *elseStmt_) {
			m_condition = condition_;
			m_trueStmt = trueStmt_;
			m_elseStmt = elseStmt_;
		}
		ExprAST *condition() const {
			return m_condition;
		}
		StmtAST *trueStmt() const {
			return m_trueStmt;
		}
		StmtAST *elseStmt() const {
			return m_elseStmt;
		}
		void accept(ASTVisitor *visitor);
	private:
		ExprAST *m_condition;
		StmtAST *m_trueStmt, *m_elseStmt;
	};

	class BlockAST : public virtual StmtAST {
	public:
		BlockAST() {
			m_stmtArray = new Array<StmtAST*>();
		}
		~BlockAST() {
			delete m_stmtArray;
		}
		void append(StmtAST *stmt) {
			m_stmtArray->append(stmt);
		}
		uint size() const {
			return m_stmtArray->size();
		}
		StmtAST *at(uint index) const {
			return m_stmtArray->at(index);
		}
		void accept(ASTVisitor *visitor);
	private:
		Array<StmtAST*> *m_stmtArray;
	};

	class ExprAST : public virtual StmtAST {
	public:
		void accept(ASTVisitor *visitor);
		virtual ~ExprAST() {
		}
	};

	class BinaryOpAST : public virtual ExprAST {
	public:
		BinaryOpAST(ExprAST *left_, Operator *op_, ExprAST *right_) {
			m_left = left_;
			m_op = op_;
			m_right = right_;
		}
		virtual ~BinaryOpAST() {

		}
		ExprAST *left() const {
			return m_left;
		}
		ExprAST *right() const {
			return m_right;
		}
		Operator *op() const {
			return m_op;
		}
		void accept(ASTVisitor *visitor);
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
		virtual	~IntLiteralAST() {
		}
		void accept(ASTVisitor *visitor);
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
		virtual ~UnaryOpAST() {
		}
		Operator *op() const {
			return m_op;
		}
		ExprAST *operand() const {
			return m_operand;
		}
		void accept(ASTVisitor *visitor);
	private:
		Operator *m_op;
		ExprAST *m_operand;
	};

	class VarAST : public virtual ExprAST {
	public:
		virtual ~VarAST() {

		}
		VarAST(const String<char_type> &varName_) {
			m_varName = varName_;
		}
		void accept(ASTVisitor *visitor);
		const ds::String<char_type> &varName() const {
			return m_varName;
		}
	private:
		ds::String<char_type> m_varName;
	};

	class ASTVisitor {
	public:
		virtual void visit(AST *) = 0;
		virtual void visit(StmtAST *) = 0;
		virtual void visit(IfStmtAST *) = 0;
		virtual void visit(BlockAST *) = 0;
		virtual void visit(ExprAST *) = 0;
		virtual void visit(BinaryOpAST *) = 0;
		virtual void visit(IntLiteralAST *) = 0;
		virtual void visit(UnaryOpAST *) = 0;
		virtual void visit(VarAST *) = 0;
		~ASTVisitor() {
		}
	private:
	};
	void AST::accept(ASTVisitor *visitor) {
		visitor->visit(this);
	}
	void StmtAST::accept(ASTVisitor *visitor) {
		visitor->visit(this);
	}
	void IfStmtAST::accept(ASTVisitor *visitor) {
		visitor->visit(this);
	}
	void BlockAST::accept(ASTVisitor *visitor) {
		visitor->visit(this);
	}
	void ExprAST::accept(ASTVisitor *visitor) {
		visitor->visit(this);
	}
	void BinaryOpAST::accept(ASTVisitor *visitor) {
		visitor->visit(this);
	}
	void UnaryOpAST::accept(ASTVisitor *visitor) {
		visitor->visit(this);
	}
	void IntLiteralAST::accept(ASTVisitor *visitor) {
		visitor->visit(this);
	}
	void VarAST::accept(ASTVisitor *visitor) {
		visitor->visit(this);
	}
}