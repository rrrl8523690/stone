// lib.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Array.hpp"
#include "String.hpp"
#include "ArrayUnitTest.hpp"
#include "StringUnitTest.hpp"


void test() {
	ArrayUnitTest::run();
	StringUnitTest::run();

}
int main() {
	test();
	return 0;
}