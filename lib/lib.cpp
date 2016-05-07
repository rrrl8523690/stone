// lib.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Array.hpp"
#include "String.hpp"
#include "ArrayUnitTest.hpp"
#include "StringUnitTest.hpp"
#include "Lexer.hpp"

#include <Windows.h>


void test() {
	ArrayUnitTest::run();
	StringUnitTest::run();

}
int main() {
	using namespace stone;
	using namespace ds;
	Lexer *lexer = new Lexer(new String<>("a = 1; b = 2; if () \n { gogo \n ; a\nsdfs_1 39.9 99 9...;"));
	Token *token;
	String<> descriptor[] = { "Id", "Str", "Num",  "Err", "Sym", };
	uint lastLineNumber = 1;
	while (token = lexer->read()) {
		if (lastLineNumber != token->lineNumber())
			std::cerr << std::endl;
		std::cerr << "(" << descriptor[token->type()] << ", " << token->string() << ")" << " ";
		lastLineNumber = token->lineNumber();
	}
	//test();
	//re::RegExpParser<char> parser("asdf");
	//re::RegExpReader<char> m_reader("fas");
	return 0;
}