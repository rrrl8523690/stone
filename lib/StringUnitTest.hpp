#pragma once

#include "String.hpp"
#include "UnitTest.hpp"

class StringUnitTest {
public:
	static void run() {
		using namespace std;
		using namespace ds;
		title("String Unit Test");
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
			equal(a == "abcdefab", true);
			equal(("abcdef" == String<>("abcdef")), true);
			equal(("aa" < String<>("b")), true);
			equal(("aa" <= String<>("ab")), true);
			equal("b" > String<>("a"), true);
			equal("b" >= String<>("a"), true);
			equal("a" == String<>("a"), true);
			equal("bad" != String<>("bac"), true);
		}
		{
			equal(String<>("abc") + 'd', "abcd");
			equal('d' + String<>("abc"), "dabc");
			String<>a = "asdfs";
			equal('g' + a + 'b' + 'c', "gasdfsbc");
			equal('g' + a + 'b' + 'c', "gasdfsbc");
			String<>t(String<>("asdf"));
			equal(t, "asdf");
			equal(t.append('a'), "asdfa");
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