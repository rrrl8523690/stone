#pragma once

#include "String.hpp"
#include "UnitTest.hpp"

class StringUnitTest {
public:
	static void run() {
		using namespace std;
		using namespace ds;
		cerr << "String Unit Test" << endl;
		{
			String<> a = "abcdef";
			String<> b;
			equal(b, String<>(""));
			b = "abced";
			equal(a < b, true);
			equal(b > a, true);
			equal(a <= b, true);
			equal(b > a, true);
			equal(a + String<>("a"), String<>("abcdefa"));
			equal((a + String<>("a")).size(), 7);
			equal(a + "a", String<>("abcdefa"));
			equal((a += a.subString(0, 2)), String<>("abcdefab"));
		}
		{
			/*int time1 = clock(), time2;
			String<> tmp;
			String<> constant = "a";
			for (uint i = 0; i < 10000000; i++) {
				tmp += constant;
			}
			tmp.clear();
			time2 = clock();
			cerr << "Time used: " << time2 - time1 << endl;
			cerr << "done" << endl;*/
		}
	}
};