#pragma once


typedef unsigned int uint;

enum ConsoleColor {
    DEFAULT = 39,
    TITLE = 34,
    CORRECT = 32,
    WRONG = 31
};

template<class T>
T min(const T &t1, const T &t2) {
    return t1 < t2 ? t1 : t2;
}

template<class T>
T max(const T &t1, const T &t2) {
    return t1 > t2 ? t1 : t2;
}

namespace stone {
    typedef char char_type;
}

void setConsoleColor(ConsoleColor color) {
    std::cerr << "\033[" << color << "m";
}
