#pragma once

#include "String.hpp"


namespace re {
	template<class CharType>
	class RegExpParser {
	public:
		RegExpParser(const String<CharType>& reString) {
			reader = new REReader(reString);
		}

		~RegExpParser() {
			delete reader;
		}
	private:
		RENode *parseRE() {
			RENode *reNode = new RENode();
			reNode->term = parseTerm();
			if (reader->hasNext()) {
				reader->read();
			}
		}

		TermNode *parseTerm() {
		}

		FactorNode *parseFactor() {
		}

		BaseNode *parseBase() {
		}

		CharSetNode *parseCharSet() {
		}
		
		REReader<CharType> *reader;
	};

	template<class CharType = char>
	class REReader {
	public:
		REReader(const String<CharType>& _reString) {
			reString = _reString;
			pos = 0;
		}

		CharType read() {
			return reString[pos++];
		}

		bool hasNext(uint step = 0) {
			return pos + step < reString.size();
		}

		CharType peek(uint step = 0) {
			return reString[pos + step];
		}

	private:
		uint pos;
		String<CharType> reString;
	};

	class RENode {
	public:
		TermNode *term;
		RENode *nextRE;
	};

	class TermNode {

	};

	class FactorNode {

	};

	class BaseNode {

	};

	class CharSetNode {
		
	};
}