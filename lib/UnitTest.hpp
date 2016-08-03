#pragma once

#include <iostream>
#include <ctime>


inline void title(const char *message) {
	setConsoleColor(TITLE);
	std::cerr << message << std::endl;
	setConsoleColor(DEFAULT);
}
#define equal(t1,t2)  \
{\
if (!((t1) == (t2))) {\
	setConsoleColor(WRONG);\
	std::cerr << "ERROR: " << (#t1) << " != " << (#t2) << std::endl\
		<< (#t1) << " = " << (t1) << ", " << (#t2) << " = " << (t2) << std::endl;\
}\
else {\
setConsoleColor(CORRECT);\
cerr << (#t1) << " == " << (#t2) << std::endl;\
}\
setConsoleColor(DEFAULT);\
}
