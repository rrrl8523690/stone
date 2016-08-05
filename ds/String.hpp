#pragma once

#include "ds/Array.hpp"
#include "ds/AutoComparable.hpp"
#include <sstream>

namespace ds {
    template<class T = char>
    class String : virtual public Array<T>, virtual public AutoComparable<String<T> > {
    public:
        String();

        String(const T *string);

        String(const String<T> &anotherString);

        String(String<T> &&anotherString);

        static String<T> number(int);

        String<T> subString(const uint &l, const uint &r) const;

        String<T> &operator=(const String<T> &anotherString);

        String<T> &operator=(String<T> &&anotherString);

        String<T> operator+(const T &character) const;

        String<T> operator+(const String<T> &anotherString) const;

        String<T> &operator+=(const String<T> &anotherString);

        bool operator<(const String<T> &anotherString) const;

        friend std::ostream &operator<<(std::ostream &os, const String<T> &str) {
            for (uint i = 0; i < str.size(); i++)
                os << str[i];
            return os;
        }

    private:
        inline void helpMove(String<T> &&anotherString) {
            if (this != &anotherString) {
                delete[] this->m_items;
                this->m_items = anotherString.m_items;
                this->m_size = anotherString.m_size;
                this->m_maxSize = anotherString.m_maxSize;
                anotherString.m_items = nullptr;
                anotherString.m_size = 0;
                anotherString.m_maxSize = 0;
            }
        }
    };

    template<class T>
    String<T>::String() {
        this->initialize();
    }

    template<class T>
    String<T>::String(const T *string) {
        uint length = 0;
        for (length = 0; string[length]; length++);
        this->resize(length);
        for (uint i = 0; string[i]; i++)
            this->m_items[i] = string[i];
    }

    template<class T>
    String<T>::String(const String<T> &anotherString) {
        this->resize(anotherString.size());
        for (uint i = 0; i < anotherString.size(); i++)
            this->m_items[i] = anotherString[i];
    }

    template<class T>
    String<T>::String(String<T> &&anotherString) {
        this->initialize();
        helpMove(std::move(anotherString));
    }

    template<class T>
    inline String<T> String<T>::subString(const uint &l, const uint &r) const {
        String<T> resultString;
        for (uint i = l; i < r; i++) {
            resultString.append(this->m_items[i]);
        }
        return resultString;
    }

    template<class T>
    String<T> String<T>::number(int num) {
        std::ostringstream oss;
        oss << num;
        std::string str = oss.str();
        String<T> res;
        for (uint i = 0; i < str.size(); i++)
            res.append(str[i]);
        return res;
    }

    template<class T>
    inline String<T> &String<T>::operator=(const String<T> &anotherString) {
        this->resize(anotherString.size());
        for (uint i = 0; i < anotherString.size(); i++) {
            this->m_items[i] = anotherString[i];
        }
        return *this;
    }

    template<class T>
    inline String<T> &String<T>::operator=(String<T> &&anotherString) {
        this->helpMove(std::move(anotherString));
        return *this;
    }

    template<class T>
    inline String<T> String<T>::operator+(const T &character) const {
        String result = *this;
        result.append(character);
        return result;
    }

    template<class T>
    inline String<T> operator+(const T &character, const String<T> &str) {
        String<T> result;
        result.resize(1);
        result[0] = character;
        return result += str;
    }

    template<class T>
    inline String<T> String<T>::operator+(const String<T> &anotherString) const {
        String<T> result;
        uint mySize = this->size(), anotherSize = anotherString.size();
        result.resize(mySize + anotherSize);
        for (uint i = 0; i < mySize; i++) {
            result[i] = this->m_items[i];
        }
        for (uint i = 0; i < anotherSize; i++) {
            result[i + mySize] = anotherString[i];
        }
        return result;
    }

    template<class T>
    inline String<T> &String<T>::operator+=(const String<T> &anotherString) {
        uint mySize = this->m_size, anotherSize = anotherString.size();
        uint newListSize = this->m_size + anotherSize;
        if (this->m_maxSize < newListSize)
            this->setMaxSize(max(newListSize, this->m_maxSize * this->m_factor));
        this->m_size = newListSize;
        for (uint i = 0; i < anotherSize; i++)
            this->m_items[i + mySize] = anotherString[i];
        return *this;
    }

    template<class T>
    inline bool String<T>::operator<(const String<T> &anotherString) const {
        return this->Array<T>::operator<(anotherString);
    }

    template<class T>
    inline bool operator==(const T *literalString, const String<T> &anotherString) {
        return anotherString == literalString;
    }

    template<class T>
    bool operator!=(const T *literalString, const String<T> &anotherString) {
        return anotherString != literalString;
    }

    template<class T>
    bool operator<(const T *literalString, const String<T> &anotherString) {
        return anotherString > literalString;
    }

    template<class T>
    bool operator<=(const T *literalString, const String<T> &anotherString) {
        return anotherString >= literalString;
    }

    template<class T>
    bool operator>(const T *literalString, const String<T> &anotherString) {
        return anotherString < literalString;
    }

    template<class T>
    bool operator>=(const T *literalString, const String<T> &anotherString) {
        return anotherString <= literalString;
    }

}
