#pragma once

#include "String.hpp"
#include "Array.hpp"
#include "RegExpReader.hpp"

namespace re {
	using namespace ds;

	template<class CharType> class RENode;
	template<class CharType> class TermNode;
	template<class CharType> class FactorNode;
	template<class CharType> class BaseNode;
	template<class CharType> class CharSetNode
	template<class CharType> class BracketsNode;

	template<class CharType = char>
	class RegExpParser {
	public:
		RegExpParser(const String<CharType>& reString) {
			reader = new RegExpReader<CharType>(reString);
			hasError = false;
		}

		~RegExpParser() {
			delete reader;
		}

	private:
		RENode<CharType> *parseRE() {
			RENode<CharType> *reNode = new RENode<CharType>();
			while (reader->hasNext()) {
				TermNode<CharType> *termNode = parseTerm();
				reNode->termArray.append(termNode);
				if (reader->hasNext()) {
					if (reader->peek() == '|') {
						reader->read();
					} else {
						error(String<>("Parsing RE, Expected '|', but received ") + reader->read());
						hasError = true;
						break;
					}
				}
			}
			return reNode;
		}

		TermNode<CharType> *parseTerm() {
			TermNode<CharType> *termNode = new TermNode<CharType>();
			while (reader->hasNext()) {
				termNode->factorArray->append(parseFactor());
			}
			return termNode;
		}

		inline static bool isUnaryOperator(const CharType& character) const {
			return character == '*' || character == '?' || character == '+';
		}

		FactorNode<CharType> *parseFactor() {
			FactorNode<CharType> *factorNode = new FactorNode<CharType>();
			factorNode->baseNode = parseBase();
			while (reader->hasNext() && isUnaryOperator(reader->peek(0))) {
				factorNode->unaryOperatorArray->append(reader->read());
			}
			return factorNode;
		}

		BaseNode<CharType> *parseBase() {
			if (reader->peek(0) == '\\') {
				reader->read();
				CharType character = reader->read();
			}
		}

		CharSetNode<CharType> *parseCharSet() {
		}

		void error(const String<>& message) const {
			setConsoleColor(WRONG);
			cerr << message << endl;
			setConsoleColor(DEFAULT);
		}

		RegExpReader<CharType> *reader;
		bool hasError;
	};





	template<class CharType>
	class RENode {
	public:
		RENode() {
			termArray = new Array<TermNode<CharType> *>();
		}
		~RENode() {
			for (uint i = 0; i < termArray->size(); i++)
				delete termArray->at(i);
			delete termArray;
		}
		Array<TermNode<CharType> *> *termArray;
	};

	template<class CharType>
	class TermNode {
	public:
		TermNode() {
			factorArray = new Array<FactorNode<CharType> *>();
		}

		~TermNode() {
			for (uint i = 0; i < factorArray->size(); i++)
				delete factorArray->at(i);
			delete factorArray;
		}

		Array<TermNode<CharType> *> *factorArray;
	};

	template<class CharType>
	class FactorNode {
	public:
		FactorNode() {
			unaryOperatorArray = new Array<CharType>();
		}

		~FactorNode() {
			delete baseNode;
			delete unaryOperatorArray;
		}

		BaseNode<CharType> *baseNode;
		Array<CharType> *unaryOperatorArray;
	};

	template<class

		template<class CharType>
	class BaseNode {
	public:

	};

	template<class CharType>
	class CharSetNode : public BaseNode<CharType> {

	};

	template<class CharType>
	class BracketsNode : public BaseNode<CharType> {

	};
}