// lib.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Array.hpp"
#include "String.hpp"
#include "ArrayUnitTest.hpp"
#include "StringUnitTest.hpp"
#include "RegExpReader.hpp"
#include "RegExpParser.hpp"
#include <Windows.h>


void test() {
	ArrayUnitTest::run();
	StringUnitTest::run();

}
int main() {
	test();
	re::RegExpParser<char> parser("asdf");
	//re::RegExpReader<char> reader("fas");
	return 0;
}