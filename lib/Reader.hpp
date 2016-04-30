#pragma once
#include "String.hpp"
using namespace ds;
template<class CharType = char>
class Reader {
public:
	virtual CharType read() = 0;
	virtual ~Reader() {
	}
};

template<class CharType = char>
class StringReader : public Reader<CharType> {
public:
	StringReader() = delete;
	StringReader(const String<CharType>& str) {
		
	}
	CharType read() {
		return
	}
private:
	uint pos;
};