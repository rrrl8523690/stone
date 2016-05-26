#pragma once

#include "Lexer.hpp"
#include "String.hpp"
#include "AST.hpp"
#include "Message.hpp"

namespace stone {
	typedef typename char char_type;
	using std::cerr;
	using std::endl;
	class Parser {
	public:
		Parser(Lexer *lexer, MsgHandler *msgHandler) {
			m_lexer = lexer;
			m_msgHandler = msgHandler;
		}
		~Parser() {
			delete m_lexer;
			delete m_msgHandler;
		}
		AST *parse() {
			AST *result = parseStmt();
			if (!m_lexer->isEnd()) { // TODO: error!
				std::cerr << "not end!" << std::endl;
			}
			if (!result)
				cerr << "null result";
			return result;
		}
		ExprAST *parseExpr(uint precedence) { // Expr(p) -> P {B Expr(q)}
			ExprAST *t = parseP();
			Token *token;
			while (!m_lexer->isEnd() && (token = m_lexer->peek(0))->type() == Token::OP
				) {
				//getPrecedence(token->string(), 2) >= precedence;
				Operator *op = (dynamic_cast<OpToken*>(token))->getOperator(2);
				if (op->precedence() < precedence)
					break;
				m_lexer->read();
				uint newPrecedence = (op->associativity() == Operator::RIGHT)
					? op->precedence() : op->precedence() + 1;
				ExprAST *t1 = parseExpr(newPrecedence);
				t = new BinaryOpAST(t, op, t1);
			}
			return t;
		}

		IfStmtAST *parseIfStmt() { // if (condition) statement [else statement]
			IfStmtAST *result = nullptr;
			expect("if");
			expect("(");
			ExprAST *conditionExpr = parseExpr(0);
			expect(")");
			StmtAST *trueStmt = parseStmt(), *elseStmt = nullptr;
			if (!m_lexer->isEnd()) {
				Token *token = m_lexer->peek(0);
				if (token->type() == Token::KEYWORD && token->string() == "else") {
					m_lexer->read();
					elseStmt = parseStmt();
				}
			}
			result = new IfStmtAST(conditionExpr, trueStmt, elseStmt);
			return result;
		}

		BlockAST *parseBlockWithBraces() {
			BlockAST *result = new BlockAST();
			//cerr << m_lexer->peek(0)->string() << m_lexer->peek(1)->string() << endl;
			expect("{");
			while (!m_lexer->isEnd()) {
				Token *token = m_lexer->peek(0);
				if (token->type() == Token::SYM && token->string() == "}") {
					m_lexer->read();
					return result;
				} else { // TODO: error
				}
				result->append(parseStmt());
			}
		}


		StmtAST *parseStmt() {
			Token *firstToken = m_lexer->peek(0);
			StmtAST *result = nullptr;
			if (firstToken->type() == Token::KEYWORD) {
				if (firstToken->string() == "if") {
					result = parseIfStmt();
				}
			} else if (firstToken->type() == Token::SYM) {
				if (firstToken->string() == "{") {
					result = parseBlockWithBraces();
				} else if (firstToken->string() == ";") {
					m_lexer->read();
					return nullptr;
				}
			} else if (firstToken->type() == Token::NUM || firstToken->type() == Token::ID) { // TODO: 
				result = new ExprStmtAST(parseExpr(0));
				expect(";");
			} else {

			}
			return result;
		}

		ExprAST *parseP() {
			Token *firstToken = m_lexer->read();
			ExprAST *result = nullptr;
			//std::cerr << "parsing P" << std::endl;
			if (firstToken->type() == Token::OP) { // P -> U Expr
				Operator *op = dynamic_cast<OpToken*>(firstToken)->getOperator(1);
				if (op) {
					if (op->type() != Operator::POSITIVE) {
						result = new UnaryOpAST(op, parseExpr(op->precedence()));
					} else {
						result = parseExpr(op->precedence());
					}
				} else { // TODO: error
				}
			} else if (firstToken->type() == Token::SYM) { // P -> "(" E ")"
				if (firstToken->string() == "(") {
					result = parseExpr(0);
					Token *token = m_lexer->read();
					if (token->type() != Token::SYM || token->string() != ")") { // TODO: error
					}
				} else { // TODO: error

				}
			} else if (firstToken->type() == Token::ID) { // P -> v
				result = new VarAST(firstToken->string());
			} else if (firstToken->type() == Token::NUM) {
				result = new IntLiteralAST(firstToken->string());
			} else { // TODO: error
			}
			return result;
		}

		void expect(const String<char_type> &string) {
			CodePosition pos(m_lexer->peek(0)->codePosition());
			if (!m_lexer->expect(string)) {
				m_msgHandler->receive(new Error(String<char_type>("expected ") + string, pos));
			}
		}

	private:
		Lexer *m_lexer;
		MsgHandler *m_msgHandler;
	};
}