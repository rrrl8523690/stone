#pragma once

#include "Array.hpp" 

namespace stone {
	typedef typename char char_type;
	class AST {
	public:
	};
	class Expr : public AST {

	};
	class BinaryOp : public Expr {
	public:
	private:
		char_type op;
		Expr *left, *right;
	};
	class IntLiteral : public Expr {
	public:
		int value() {
			return m_value;
		}
	private:
		int m_value;
	};
}