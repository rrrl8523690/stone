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
