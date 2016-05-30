#pragma once

#include "Token.hpp"
#include "String.hpp"
#include "Reader.hpp"

namespace stone {
	using namespace ds;
	typedef char char_type;
	class Lexer {
	public:
		Lexer(String<char_type> *string) {// TODO: change it to Reader
			m_reader = new StringReader<char_type>(string);
			m_head = 0;
			m_lineNumber = 1;
		}

		Token *read() {
			if (!fillTokens(1))
				return nullptr;
			return m_tokens[m_head++];
		}

		bool expect(const String<char_type> &string_) {
			Token *token;
			if ((token = read())->string() != string_) {
				std::cerr << "Lexer error at line " << token->lineNumber() << ": expected " << string_ << ", received " << token->string() << std::endl;
				return false;
			}
			return true;
		}

		bool isEnd() {
			return !fillTokens(1);
		}

		Token *peek(int step) {
			if (!fillTokens(step + 1))
				return nullptr;
			return m_tokens[m_head + step];
		}

		~Lexer() {
			delete m_reader;
		}
	private:
		static bool isInCharSet(char_type ch, char_type charset[]) {
			for (uint i = 0; charset[i]; i++)
				if (ch == charset[i])
					return true;
			return false;
		}
		static bool isBlankChar(char_type ch) {
			static char_type blankCharSet[] = " \t";
			return isInCharSet(ch, blankCharSet);
		}
		bool isOp(char_type ch) {
			static char_type opBeginCharSet[] = "|&^!+-*/=<>";
			return isInCharSet(ch, opBeginCharSet);
		}
		bool isSymbol(char_type ch) {
			static char_type symbolBeginCharSet[] = ";,.[](){}";
			return isInCharSet(ch, symbolBeginCharSet);
		}
		bool couldBeLonger(char_type ch) {
			static char_type couldBeLongerCharSet[] = "><=+-&|";
			return isInCharSet(ch, couldBeLongerCharSet);
		}
		bool isNum(char_type ch) {
			return '0' <= ch && ch <= '9';
		}
		bool isLetter(char_type ch) {
			return ('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z');
		}
		bool isInStringSet(const String<char_type> &string, const Array<String<char_type> > &stringSet) {
			for (uint i = 0; i < stringSet.size(); i++)
				if (string == stringSet[i])
					return true;
			return false;
		}
		bool isKeyword(const String<char_type> &string) {
			static Array<String<char_type> > keywordSet = { "if", "else", "while", "for", "def"};
			return isInStringSet(string, keywordSet);
		}
		bool fillAToken(Reader<char_type> *reader) {
			char_type ch;
			m_kth++;
			while (!reader->isEnd()) {
				ch = reader->read();
				if (!isBlankChar(ch))
					break;
				reader->next();
			}
			if (reader->isEnd())
				return false;
			String<char_type> string;
			if ('_' == ch || isLetter(ch)) { // IdToken or KeywordToken
				while (!reader->isEnd()) {
					ch = reader->read();
					if (isLetter(ch) || '_' == ch || isNum(ch))
						string.append(ch);
					else
						break;
					reader->next();
				}
				if (isKeyword(string))
					m_tokens.append(new KeywordToken(string, m_lineNumber, m_kth));
				else
					m_tokens.append(new IdToken(string, m_lineNumber, m_kth));
				return true;
			} else if (isNum(ch)) { // NumToken
				int visDot = 0;
				while (!reader->isEnd()) {
					ch = reader->read();
					if (isNum(ch) || ('.' == ch)) {
						string.append(ch);
						visDot += ('.' == ch);
					} else break;
					reader->next();
				}
				if (visDot <= 1)
					m_tokens.append(new NumToken(string, m_lineNumber, m_kth));
				else
					m_tokens.append(new ErrToken(string, m_lineNumber, m_kth));
			} else if (isOp(ch)) { // OpToken
				string.append(ch);
				reader->next();
				char_type ch2 = reader->read(); // does not support << and >> currently
				if ((ch2 == '=' && isInCharSet(ch, "+-*/&|^!><")) ||
					(ch == ch2 && isInCharSet(ch, "+-&|="))) {
					string.append(ch2);
					reader->next();
				}
				m_tokens.append(new OpToken(string, m_lineNumber, m_kth));
			} else if (isSymbol(ch)) {
				string.append(ch);
				m_tokens.append(new SymToken(string, m_lineNumber, m_kth));
				reader->next();
			} else { //ErrToken
				m_tokens.append(new ErrToken(string, m_lineNumber, m_kth));
				reader->next();
			}
			return true;
		}
		bool fillTokens(uint atLeast = 1) {
			if (m_tokens.size() - m_head >= atLeast)
				return true;
			while (!m_reader->isEnd() && m_tokens.size() - m_head < atLeast) {
				String<char_type> line = m_reader->readLine();
				Reader<char_type> *lineReader = new StringReader<char_type>(&line);
				while (!lineReader->isEnd()) {
					fillAToken(lineReader);
				}
				m_lineNumber++;
				m_kth = 0;
			}
			return m_tokens.size() - m_head >= atLeast;
		}

		Reader<char_type> *m_reader;
		Array<Token*> m_tokens;
		uint m_head;
		uint m_lineNumber, m_kth;
	};
}