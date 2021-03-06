#pragma once

#include <iostream>
#include "ds/String.hpp"
#include "common/Common.h"

namespace stone {
    using namespace ds;

    class CodePosition {
    public:
        CodePosition(uint line_, uint kth_) {
            m_line = line_;
            m_kth = kth_;
        }

        inline uint line() const {
            return m_line;
        }

        inline uint kth() const {
            return m_kth;
        }

        ds::String<> toString() const {
            return ds::String<>::number(m_line) + ", " + ds::String<>::number(m_kth);
        }

    private:
        uint m_line, m_kth;
    };

    class Token {
    public:
        enum TokenType {
            ID,
            KEYWORD,
            STR,
            NUM,
            ERR,
            OP,
            SYM
        };

        Token(const String<char_type> &string, uint lineNumber_, uint kth_) : m_codePosition(lineNumber_, kth_) {
            m_string = string;
        }

        virtual const String<char_type> &string() const {
            return m_string;
        }

        virtual const CodePosition &codePosition() const {
            return m_codePosition;
        }

        virtual uint lineNumber() const {
            return m_codePosition.line();
        }

        virtual uint kth() const {
            return m_codePosition.kth();
        }

        virtual TokenType type() = 0;

        virtual ~Token() {

        }

    private:
        String<char_type> m_string;
        CodePosition m_codePosition;
    };

    class IdToken : public Token {
    public:
        IdToken(const String<char_type> &string, uint lineNumber_, uint kth_) : Token(string, lineNumber_, kth_) {

        }

        TokenType type() {
            return ID;
        }
    };

    class KeywordToken : public Token {
    public:
        KeywordToken(const String<char_type> &string, uint lineNumber_, uint kth_) : Token(string, lineNumber_, kth_) {

        }

        TokenType type() {
            return KEYWORD;
        }
    };

    class NumToken : public Token {
    public:
        NumToken(const String<char_type> &string, uint lineNumber_, uint kth_) : Token(string, lineNumber_, kth_) {

        }

        TokenType type() {
            return NUM;
        }
    };

    class Operator {
    public:
        enum Associativity {
            LEFT,
            RIGHT,
        };
        enum OpType {
            ASSIGN,
            ADD, SUB,
            MUL, DIV, MOD,
            ORELSE, ANDALSO,
            POSITIVE, NEGATIVE,
            LESS, GREATER, NOTLESS, NOTGREATER,
            EQUAL, NOTEQUAL
        };

        Operator(const String<char_type> &opString, uint precedence_, Associativity associativity_, uint operandNum_,
                 OpType opType_) {
            m_string = opString;
            init(precedence_, associativity_, operandNum_, opType_);
        }

        const String<char_type> &string() const {
            return m_string;
        }

        uint precedence() const {
            return m_precedence;
        }

        Associativity associativity() const {
            return m_associativity;
        }

        uint operandNum() const {
            return m_operandNum;
        }

        OpType type() const {
            return m_opType;
        }

        int calculate(int a, int b) {
            switch (m_opType) {
                case ADD:
                    return a + b;
                case SUB:
                    return a - b;
                case MUL:
                    return a * b;
                case DIV:
                    return a / b;
                case MOD:
                    return a % b;
                case EQUAL:
                    return a == b;
                case NOTEQUAL:
                    return a != b;
                case LESS:
                    return a < b;
                case GREATER:
                    return a > b;
                case NOTLESS:
                    return a >= b;
                case NOTGREATER:
                    return a <= b;
                default:
                    std::cerr << "No such operator!" << std::endl;
            }
            return 0;
        }

    private:
        void init(uint precedence_, Associativity associativity_, uint operandNum_, OpType opType_) {
            m_precedence = precedence_;
            m_associativity = associativity_;
            m_operandNum = operandNum_;
            m_opType = opType_;
        }

        String<char_type> m_string;
        uint m_precedence;
        Associativity m_associativity;
        uint m_operandNum;
        OpType m_opType;
    };

    Operator assignOp("=", 0, Operator::RIGHT, 2, Operator::ASSIGN);
    Operator orElseOp("||", 2, Operator::LEFT, 2, Operator::ORELSE);
    Operator andAlsoOp("&&", 3, Operator::LEFT, 2, Operator::ANDALSO);
    Operator equalOp("==", 4, Operator::LEFT, 2, Operator::EQUAL);
    Operator lessOp("<", 4, Operator::LEFT, 2, Operator::LESS);
    Operator greaterOp(">", 4, Operator::LEFT, 2, Operator::GREATER);
    Operator notLessOp(">=", 4, Operator::LEFT, 2, Operator::NOTLESS);
    Operator notGreaterOp("<=", 4, Operator::LEFT, 2, Operator::NOTGREATER);
    Operator notEqualOp("!=", 4, Operator::LEFT, 2, Operator::NOTEQUAL);
    Operator addOp("+", 5, Operator::LEFT, 2, Operator::ADD);
    Operator subOp("-", 5, Operator::LEFT, 2, Operator::SUB);
    Operator mulOp("*", 7, Operator::LEFT, 2, Operator::MUL);
    Operator divOp("/", 7, Operator::LEFT, 2, Operator::DIV);
    Operator modOp("%", 7, Operator::LEFT, 2, Operator::MOD);
    Operator negativeOp("-", 6, Operator::LEFT, 1, Operator::NEGATIVE);
    Operator positiveOp("+", 6, Operator::LEFT, 1, Operator::POSITIVE);

//    extern Operator assignOp, orElseOp, andAlsoOp, equalOp, notEqualOp, addOp, subOp, mulOp, divOp, modOp, negativeOp, positiveOp, lessOp, greaterOp, notLessOp, notGreaterOp;

    Array<Operator *> opArray = {&assignOp, &orElseOp, &andAlsoOp, &equalOp, &notEqualOp, &addOp, &subOp, &mulOp,
                                 &divOp, &modOp, &positiveOp, &negativeOp, &lessOp, &greaterOp, &notLessOp,
                                 &notGreaterOp};

    class OpToken : public Token {
    public:
        OpToken(const String<char_type> &string, uint lineNumber_, uint kth_) : Token(string, lineNumber_, kth_) {

        }

        Operator *getOperator(uint operandNum) {
            for (uint i = 0; i < opArray.size(); i++) {
                if (operandNum == opArray[i]->operandNum() && string() == opArray[i]->string())
                    return opArray[i];
            }
            std::cerr << "Operator not found!" << std::endl;
            return nullptr;
        }

        TokenType type() {
            return OP;
        }
    };

    class SymToken : public Token {
    public:
        SymToken(const String<char_type> &string, uint lineNumber_, uint kth_) : Token(string, lineNumber_, kth_) {

        }

        TokenType type() {
            return SYM;
        }
    };

    class ErrToken : public Token {
    public:
        ErrToken(const String<char_type> &string, uint lineNumber_, uint kth_) : Token(string, lineNumber_, kth_) {
        }

        TokenType type() {
            return ERR;
        }
    };
}