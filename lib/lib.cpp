// lib.cpp : �������̨Ӧ�ó������ڵ㡣
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