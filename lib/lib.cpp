// lib.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Array.hpp"
#include "String.hpp"
#include "ArrayUnitTest.hpp"
#include "StringUnitTest.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Visitor.hpp"


void dsUnitTest() {
	ArrayUnitTest::run();
	StringUnitTest::run();

}
void stoneTest() {
	using namespace stone;
	using namespace ds;
	std::fstream inputFileStream("test.stone", std::ios::in);
	String<> code;
	char ch;
	while ((ch = inputFileStream.get()) != EOF) {
		code.append(ch);
	}
	std::cerr << code << std::endl;
	std::cerr << std::endl;
	Lexer *lexer = new Lexer(&code);
	Token *token;
	String<> descriptor[] = { "Id", "Str", "Num",  "Err", "Op", "Sym", };
	uint lastLineNumber = 1;
	while (token = lexer->read()) {
		if (lastLineNumber != token->lineNumber())
			std::cerr << std::endl;
		std::cerr << "(" << descriptor[token->type()] << ", " << token->string() << ")" << " ";
		if (token->type() == Token::OP) {
			if (((OpToken*)token)->getOperator(2))
				std::cerr << ((OpToken*)token)->getOperator(2)->type() << std::endl;
		}
		lastLineNumber = token->lineNumber();
	}
}

void visitorTest() {
	using namespace test;
	Node *node = new Node1();
	Visitor *visitor = new Visitor1();
	node->accept(visitor);
}
int main() {
	visitorTest();
	//stoneTest();
	//test();
	//re::RegExpParser<char> parser("asdf");
	//re::RegExpReader<char> m_reader("fas");
	return 0;
}