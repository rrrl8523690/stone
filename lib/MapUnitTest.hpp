#pragma once

#include "Map.hpp"
#include "TreeMapImpl.hpp"
#include "UnitTest.hpp"
#include "String.hpp"
#include <algorithm>

namespace ds {
	class MapUnitTest {
	public:
		static void run() {
			using namespace std;
			title("Map Unit Test");
			{
				Map<int, int> map;
				Array<int> order;
				int n = 100000;
				for (int i = 1; i <= n; i++) {
					order.append(i);
				}
				for (int i = n - 1; i >= 0; i--) {
					int x;
					x = rand() % (i + 1);
					std::swap(order[i], order[x]);
				}
				for (uint i = 0; i < order.size(); i++) {
					map[order[i]] = order[i];
				}
				bool ok = true;
				for (int i = 1; i <= n; i++) {
					if (map[i] != i) {
						ok = false;
						std::cerr << i << " " << map[i] << std::endl;
					}
				}
				if (ok) {
					std::cerr << "DONE, Nothing wrong" << std::endl;
				}
			}
		}
	};
}