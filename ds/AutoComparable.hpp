# pragma once

#include <iostream>
// T provides operator <
namespace ds {
    template<class T>
    class AutoComparable {
    public:
        friend bool operator==(const T &t1, const T &t2) {
            return !(t1 < t2) && !(t2 < t1);
        }

        friend bool operator!=(const T &t1, const T &t2) {
            return !(t1 == t2);
        }

        friend bool operator>(const T &t1, const T &t2) {
            return t2 < t1;
        }

        friend bool operator<=(const T &t1, const T &t2) {
            return t1 < t2 || t1 == t2;
        }

        friend bool operator>=(const T &t1, const T &t2) {
            return t2 < t1 || t1 == t2;
        }
    };
}