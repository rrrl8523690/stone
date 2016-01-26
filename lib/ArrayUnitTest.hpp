#pragma once

#include "Array.hpp"
#include "UnitTest.hpp"
#include <iostream>
#include <ctime>
using namespace std;

class ArrayUnitTest {
public:
	void run() {
		using namespace ds;
		{
			int arr[] = { 1, 2, 3 };
			Array<int> a(arr, 2);
			Array<int> b;
			b.append(1);
			b.append(2);
			equal(a, b);
			b.resize(1); // b: {1}
		}
		{
			Array<int> a;
			a.append(1).append(3).append(2);
			Array<int> b = a;
			b.append(2);
			//cerr << a << " " << b << endl;
		}
		{

			int arr1[] = { 1, 2, 3, 2 };
			int arr2[] = { 1, 2, 4, 1 };
			Array<int> a(arr1, 4), b(arr2, 4);
			cerr << (a + b).append(2) << endl;
			//auto c = a + b;
			//cerr << c.append(2) << endl;
			//cerr << a + b << endl;
			/* cerr << b + a << endl;
			a += b;
			cerr << a << endl;
			a += a;
			cerr << a << endl;*/
		}

		//Array<int> lst;
		//int time1 = clock(), time2;
		//for (uint times = 0; times < 5; times++) {
		//	lst.resize(0);
		//	for (uint i = 0; i < 1000000; i++) {
		//		lst.append(i);
		//	}
		//	lst.resize(times);
		//	time2 = clock();
		//	cerr << time2 - time1 << endl;
		//	time1 = time2;
		//	equal(lst, Array<int>());
		//}

	}
};