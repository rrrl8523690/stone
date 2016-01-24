#pragma once

#include "Array.hpp"
#include "UnitTest.hpp"
#include <iostream>
using namespace std;

class ArrayUnitTest {
public:
	void run() {
		using namespace ds;
		int arr[] = { 1, 2, 3 };
		Array<int> a(arr, 3);
		Array<int> b;
		b.append(1);
		b.append(2);
		equal(a, b);
	}
};