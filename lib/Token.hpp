#pragma once

#include "String.hpp"
namespace stone {
	using namespace ds;
	typedef char char_type;
	class Token {
	public:
		enum TokenType {
			ID,
			STR,
			NUM,
			ERR,
			OP,
			SYM
		};
		Token(const String<char_type> &string, uint lineNumber) {
			m_string = string;
			m_lineNumber = lineNumber;
		}
		virtual const String<char_type> &string() const {
			return m_string;
		}
		virtual uint lineNumber() const {
			return m_lineNumber;
		}
		virtual TokenType type() = 0;
		virtual ~Token() {

		}
	private:
		String<char_type> m_string;
		uint m_lineNumber;
	};

	class IdToken : public Token {
	public:
		IdToken(const String<char_type> &string, uint lineNumber) : Token(string, lineNumber) {

		}
		TokenType type() {
			return ID;
		}
	};

	class NumToken : public Token {
	public:
		NumToken(const String<char_type> &string, uint lineNumber) : Token(string, lineNumber) {

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
			MUL, DIV,
			ORELSE, ANDALSO,
			POSITIVE, NEGATIVE,
			EQUAL, NOTEQUAL
		};
		Operator(const String<char_type>& opString, uint precedence_, Associativity associativity_, uint operandNum_, OpType opType_) {
			m_string = opString;
			init(precedence_, associativity_, operandNum_, opType_);
		}
		const String<char_type>& string() const {
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

	extern Operator assignOp("=", 0, Operator::RIGHT, 2, Operator::ASSIGN);
	extern Operator orElseOp("||", 2, Operator::LEFT, 2, Operator::ORELSE);
	extern Operator andAlsoOp("&&", 3, Operator::LEFT, 2, Operator::ANDALSO);
	extern Operator equalOp("==", 4, Operator::LEFT, 2, Operator::EQUAL);
	extern Operator notEqualOp("!=", 4, Operator::LEFT, 2, Operator::NOTEQUAL);
	extern Operator addOp("+", 5, Operator::LEFT, 2, Operator::ADD);
	extern Operator subOp("-", 5, Operator::LEFT, 2, Operator::SUB);
	extern Operator mulOp("*", 7, Operator::LEFT, 2, Operator::MUL);
	extern Operator divOp("/", 7, Operator::LEFT, 2, Operator::DIV);
	extern Operator negativeOp("-", 6, Operator::LEFT, 1, Operator::NEGATIVE);
	extern Operator positiveOp("+", 6, Operator::LEFT, 1, Operator::POSITIVE);

	Array <Operator*> opArray = { &assignOp, &orElseOp, &andAlsoOp, &equalOp, &addOp, &subOp, &mulOp, &divOp , &positiveOp, &negativeOp };

	class OpToken : public Token {
	public:
		OpToken(const String<char_type> &string, uint lineNumber) : Token(string, lineNumber) {

		}
		Operator *getOperator(uint operandNum) {
			for (uint i = 0; i < opArray.size(); i++) {
				if (operandNum == opArray[i]->operandNum() && string() == opArray[i]->string())
					return opArray[i];
			}
			return nullptr;
		}
		TokenType type() {
			return OP;
		}
	};
	class SymToken : public Token {
	public:
		SymToken(const String<char_type> &string, uint lineNumber) : Token(string, lineNumber) {

		}
		TokenType type() {
			return SYM;
		}
	};

	class ErrToken : public Token {
	public:
		ErrToken(const String<char_type> &string, uint lineNumber) : Token(string, lineNumber) {
		}
		TokenType type() {
			return ERR;
		}
	};
}