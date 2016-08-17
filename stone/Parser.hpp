#pragma once

#include "stone/Lexer.hpp"
#include "ds/String.hpp"
#include "stone/AST.hpp"
#include "stone/Message.hpp"

namespace stone {
    typedef char char_type;
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
            AST *result = parseBlockWithoutBraces();
            if (!m_lexer->isEnd()) { // TODO: error!
                std::cerr << "not end!" << std::endl;
            }
            if (!result)
                cerr << "null result";
            return result;
        }


        IfStmtAST *parseIfStmt() { // if (condition) statement [else statement]
            IfStmtAST *result = nullptr;
            expect("if");
            expect("(");
            ExprAST *conditionExpr = parseExpr(0);
            expect(")");
            StmtAST *trueStmt = parseStmt(), *elseStmt = StmtAST::nullStmt();
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

        WhileStmtAST *parseWhileStmt() {
            expect("while");
            expect("(");
            ExprAST *condition = parseExpr(0);
            expect(")");
            StmtAST *trueStmt = parseStmt();
            WhileStmtAST *result = new WhileStmtAST(condition, trueStmt);
            return result;
        }

        ForStmtAST *parseForStmt() {
            expect("for");
            expect("(");
            ExprAST *init = nullptr, *condition = nullptr, *step = nullptr;
            if (!(m_lexer->peek(0)->type() == Token::SYM) || m_lexer->peek(0)->string() != ";") {
                init = parseExpr(0);
            }
            expect(";");
            if (!(m_lexer->peek(0)->type() == Token::SYM) || m_lexer->peek(0)->string() != ";") {
                condition = parseExpr(0);
            }
            expect(";");
            if (!(m_lexer->peek(0)->type() == Token::SYM) || m_lexer->peek(0)->string() != ")") {
                step = parseExpr(0);
            }
            expect(")");
            StmtAST *body = parseStmt();
            return new ForStmtAST(init, condition, step, body);
        }

        BlockAST *parseBlockWithBraces() {
            BlockAST *result = new BlockAST();
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
            return result;
        }

        BlockAST *parseBlockWithoutBraces() {
            BlockAST *result = new BlockAST();
            while (!m_lexer->isEnd()) {
                //cerr << m_lexer->peek(0)->string();
                result->append(parseStmt());
            }
            return result;
        }

        Array<ExprAST *> *parseActualParams() {
            Array<ExprAST *> *params = new Array<ExprAST *>();
            bool isFirstParam = true;
            while (!m_lexer->isEnd() && m_lexer->peek(0)->string() != ")") {
                if (!isFirstParam) {
                    expect(",");
                } else {
                    isFirstParam = false;
                }
                params->append(parseExpr(0));
            }
            return params;
        }

        Array<ParamValuePair *> *parseFormalParams() {
            Array<ParamValuePair *> *params = new Array<ParamValuePair *>();
            bool isFirstParam = true;
            while (!m_lexer->isEnd() && m_lexer->peek(0)->string() != ")") {
                if (!isFirstParam) {
                    expect(",");
                } else {
                    isFirstParam = false;
                }
                Token *token = m_lexer->read();
                if (token->type() == Token::ID) {
                    String<char_type> paramName = token->string();
                    ExprAST *value = nullptr;
                    if (m_lexer->peek(0)->string() == "=") {
                        m_lexer->read();
                        value = parseExpr(0);
                    }
                    params->append(new ParamValuePair(paramName, value));
                } else { //TODO: error
                }
            }
            return params;
        }

        DefFuncStmtAST *parseDefFuncStmt() {
            expect("def");
            Token *funcNameToken = m_lexer->read();
            String<char_type> funcName;
            if (funcNameToken->type() == Token::ID) {
                funcName = funcNameToken->string();
            } else { // TODO: error
            }
            expect("(");
            Array<ParamValuePair *> *params = parseFormalParams();
            expect(")");
            BlockAST *funcBody = parseBlockWithBraces();
            return new DefFuncStmtAST(funcName, params, funcBody);
        }


        PrintStmtAST *parsePrintStmt() {
            expect("print");
            ExprAST *expr = parseExpr(0);
            expect(";");
            return new PrintStmtAST(expr);
        }

        StmtAST *parseStmt() {
            Token *firstToken = m_lexer->peek(0);
            StmtAST *result = nullptr;
            if (firstToken->type() == Token::KEYWORD) {
                if (firstToken->string() == "if") {
                    result = parseIfStmt();
                } else if (firstToken->string() == "while") {
                    result = parseWhileStmt();
                } else if (firstToken->string() == "def") {
                    result = parseDefFuncStmt();
                } else if (firstToken->string() == "print") {
                    result = parsePrintStmt();
                } else if (firstToken->string() == "for") {
                    result = parseForStmt();
                }
            } else if (firstToken->type() == Token::SYM) {
                if (firstToken->string() == "{") {
                    result = parseBlockWithBraces();
                } else if (firstToken->string() == ";") {
                    m_lexer->read();
                    return StmtAST::nullStmt();
                } else if (firstToken->string() == "(") {
                    result = new ExprStmtAST(parseExpr(0));
                    expect(";");
                }
            } else if (firstToken->type() == Token::NUM || firstToken->type() == Token::ID) { // TODO:
                result = new ExprStmtAST(parseExpr(0));
                expect(";");
            } else { // TODO: ERROR
            }
            return result;
        }

        PostfixAST *parsePostfix() {
            if (m_lexer->isEnd())
                return nullptr;
            Token *symbolToken = m_lexer->peek(0);
            PostfixAST *result = nullptr;
            if (symbolToken->string() == "[" || symbolToken->string() == "." ||
                symbolToken->string() == "(") {
                Token *symbolToken = m_lexer->read();
                if (symbolToken->string() == "[") { // array index: [Expr]
                    ExprAST *indexExprAST = parseExpr(0);
                    result = new IndexPostfixAST(indexExprAST, symbolToken->codePosition());
                    expect("]");
                } else if (symbolToken->string() == ".") { // member: .memberName
                    Token *memberNameToken = m_lexer->read();
                    if (memberNameToken->type() != Token::ID) { // TODO: ERROR
                    }
                    result = new MemberPostfixAST(memberNameToken->string());
                } else if (symbolToken->string() == "(") { // TODO: fix
                    Array<ExprAST *> *params = parseActualParams();
                    expect(")");
                    result = new CallFuncPostfixAST(params, symbolToken->codePosition());
                }
            } else { // TODO: ERROR
            }
            return result;
        }

        ExprAST *parseExpr(uint precedence) { // Expr(p) -> P {B Expr(q)}
            ExprAST *t = parseP();
            Token *token;
            while (!m_lexer->isEnd() && (token = m_lexer->peek(0))->type() == Token::OP
                    ) {
                //getPrecedence(token->string(), 2) >= precedence;
                Operator *op = (dynamic_cast<OpToken *>(token))->getOperator(2);
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

        ArrayExprAST *parseArrayExpr() { // parse the array expression without the braces on both sides
            Token *firstToken;
            ArrayExprAST *result;
            Array<ExprAST *> *exprs = new Array<ExprAST *>();
            bool isFirst = true;
            while (!m_lexer->isEnd() && m_lexer->peek(0)->string() != "]") {
                if (!isFirst) {
                    expect(",");
                }
                exprs->append(parseExpr(0));
                isFirst = false;
            }
            result = new ArrayExprAST(exprs);
            return result;
        }

        ExprAST *parseP() {
            Token *firstToken = m_lexer->read();
            ExprAST *result = nullptr;
            //std::cerr << "parsing P" << std::endl;
            if (firstToken->type() == Token::OP) { // P -> U Expr
                Operator *op = dynamic_cast<OpToken *>(firstToken)->getOperator(1);
                if (op) {
                    if (op->type() != Operator::POSITIVE) {
                        result = new UnaryOpAST(op, parseExpr(op->precedence()));
                    } else {
                        result = parseExpr(op->precedence());
                    }
                } else { // TODO: error
                }
            } else if (firstToken->type() == Token::SYM) { // P -> "(" E ")" [Postfixes] or P -> "[" E, E, E... "]"
                if (firstToken->string() == "(" || firstToken->string() == "[") {
                    if (firstToken->string() == "(") {
                        result = parseExpr(0);
                        expect(")");
                    } else if (firstToken->string() == "[") {
                        result = parseArrayExpr();
                        expect("]");
                    }
                    PostfixAST *postfix;
                    while ((postfix = parsePostfix()))
                        result->appendPostfix(postfix);
                } else { // TODO: error
                }

            } else if (firstToken->type() == Token::ID) { // P -> v [Postfixes]
                result = new VarAST(firstToken->string(), firstToken->codePosition());
                PostfixAST *postfix;
                while ((postfix = parsePostfix()))
                    result->appendPostfix(postfix);
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