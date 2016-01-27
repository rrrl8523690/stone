#pragma once

#include <iostream>
#include <ctime>
#include <Windows.h>

inline void setConsoleColor(int colorId) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorId);
}
inline void title(const char *message) {
	setConsoleColor(13);
	std::cerr << message << std::endl;
	setConsoleColor(7);
}
#define equal(t1,t2)  \
{\
if (!((t1) == (t2))) {\
	setConsoleColor(207);\
	std::cerr << "ERROR: " << (#t1) << " != " << (#t2) << std::endl\
		<< (#t1) << " = " << (t1) << ", " << (#t2) << " = " << (t2) << std::endl;\
}\
else {\
setConsoleColor(2);\
cerr << (#t1) << " == " << (#t2) << std::endl;\
}\
setConsoleColor(7);\
}
