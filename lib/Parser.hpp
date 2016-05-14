#pragma once

#include "Lexer.hpp"
#include "String.hpp"
#include "AST.hpp"

namespace stone {
	typedef typename char char_type;
	class Parser {
	public:
		Parser(Lexer *lexer) {
			m_lexer = lexer;
		}
		AST *parse() {
			return parseExpr(0);
		}
		UnaryOp *parseUnaryOp() {
		}
		Expr *parseExpr(uint precedence) {
			Expr *t = parseUnaryOp();
			Token *token;
			while ((token = m_lexer->read())->type() == Token::OP &&  getPrecedence(token->string(), 2) >= precedence) {

			}
		}

	private:
		static uint getPrecedence(const String<char_type> &op, const uint operandNum) {
			if (operandNum == 1) {
				if (op == "+" || op == "-")
					return 4;
			} else if (operandNum == 2) {
				if (op == "||")
					return 0;
				if (op == "&&")
					return 1;
				if (op == "=")
					return 2;
				if (op == "+" || op == "-")
					return 3;
				if (op == "*" || op == "/")
					return 5;
				if (op == "^")
					return 6;
			}
		}
		Lexer *m_lexer;
	};
}