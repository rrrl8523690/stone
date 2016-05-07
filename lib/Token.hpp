#pragma once

#include "String.hpp"
namespace stone {
	using namespace ds;
	typedef char char_type;
	enum TokenType {
		ID,
		STR,
		NUM,
		ERR,
		SYM
	};
	class Token {
	public:
		Token(const String<char_type> &string) {
			m_string = string;
		}
		virtual const String<char_type> &string() {
			return m_string;
		}
		virtual TokenType type() = 0;
		virtual ~Token() {

		}
	private:
		String<char_type> m_string;
	};

	class IdToken : public Token {
	public:
		IdToken(const String<char_type> &string) : Token(string) {

		}
		TokenType type() {
			return ID;
		}
	};

	class NumToken : public Token {
	public:
		NumToken(const String<char_type> &string) : Token(string) {

		}
		TokenType type() {
			return NUM;
		}
	};

	class SymToken : public Token {
	public:
		SymToken(const String<char_type> &string) : Token(string) {
			
		}
		TokenType type() {
			return SYM;
		}
	};

	class ErrToken : public Token {
	public:
		ErrToken(const String<char_type> &string) : Token(string) {
		}
		TokenType type() {
			return ERR;
		}
	};
}