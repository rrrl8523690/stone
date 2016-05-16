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
			AST *result = parseExpr(0);
			if (!m_lexer->isEnd()) { // TODO: error!
			}
			return result;
		}
		UnaryOpAST *parseUnaryOp() {
		}
		ExprAST *parseExpr(uint precedence) { // Expr(p) -> P {B Expr(q)}
			ExprAST *t = parseP();
			Token *token;
			while ((token = m_lexer->read())->type() == Token::OP
				&& getPrecedence(token->string(), 2) >= precedence) {
				Operator *op = (dynamic_cast<OpToken*>(token))->getOperator(2);
				uint newPrecedence = (op->associativity() == Operator::RIGHT) ? precedence : precedence + 1;
				ExprAST *t1 = parseExpr(newPrecedence);
				t = new BinaryOpAST(t, op, t1);
			}
			return t;
		}
		ExprAST *parseP() {
			Token *firstToken = m_lexer->read();
			ExprAST *result;
			if (firstToken->type() == Token::OP) {
				Operator *op = dynamic_cast<OpToken*>(firstToken)->getOperator(1);
				if (op) {
					if (op->type() != Operator::POSITIVE) {
						result = new UnaryOpAST(op, parseExpr(op->precedence()));
					} else {
						result = parseExpr(op->precedence());
					}
				} else { // TODO: error

				}
			} else if (firstToken->type() == Token::SYM) {
				if (firstToken->string() == "(") {
					result = parseExpr(0);
					Token *token = m_lexer->read();
					if (token->type() != Token::SYM || token->string() != ")") { // TODO: error
					}
				}
			} else if (firstToken->type() == Token::ID) {
				result = new VarAST(firstToken->string());
			} else { // TODO: error
			}
			return result;
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