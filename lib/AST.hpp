#pragma once

#include "Array.hpp" 
#include "String.hpp"

namespace stone {
	typedef typename char char_type;
	class AST {
	public:
	};
	class Expr : public AST {

	};
	class BinaryOp : public Expr {
	public:
		enum OpType {
			ADD, SUB,
			MUL, DIV,
			AND, OR,
			ANDALSO,
			ORELSE,
			ERR,
			POSITVE, NEGATIVE,
		};
		static OpType getOpType(const String<char_type> &opString, const uint operandNum) {
			static String<char_type> binOps[] = { "+" , "-" , "*", "/", "&", "/", "&&", "||" };
			uint size = ERR;
			uint i;
			for (i = 0; i < size; i++) {
				if (binOps[i] == opString)
					break;
			}
			if (operandNum == 1) {
				if (opString == "+")
					return POSITVE;
				if (opString == "-")
					return NEGATIVE;
			}
			return OpType(i);
		}
	private:
		OpType m_op;
		Expr *m_left, *m_right;
	};

	class IntLiteral : public Expr {
	public:
		IntLiteral(const String<char_type> &numString) {
			int res = 0;
			for (uint i = 0; i < numString.size(); i++) {
				res *= 10;
				res += numString[i] - '0';
			}
			m_value = res;
		}
		int value() {
			return m_value;
		}
	private:
		int m_value;
	};

	class UnaryOp : public Expr {
		enum OpType {
			NONE,
			POSITIVE, NEGATIVE,
		};
		OpType m_op;
		Expr *m_operand;
	};

	class Var : public Expr {
	public:
		const ds::String<char_type> &varName() const {
			return m_varName;
		}
	private:
		ds::String<char_type> m_varName;
	};
}