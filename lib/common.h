#pragma once

#include <Windows.h>

typedef unsigned int uint;

enum ConsoleColor {
	DEFAULT = 7,
	TITLE = 13,
	CORRECT = 2,
	WRONG = 207
};

inline void setConsoleColor(const ConsoleColor& colorId) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorId);
}

template<class T>
const T& min(const T& t1, const T& t2) {
	if (t1 < t2)
		return t1;
	return t2;
}

template<class T>
const T& max(const T& t1, const T& t2) {
	if (t1 > t2)
		return t1;
	return t2;
}
