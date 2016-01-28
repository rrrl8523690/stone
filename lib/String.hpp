#pragma once

#include "Array.hpp"

namespace ds {
	template<class T = char>
	class String : public Array<T> {
	public:
		String();
		String(const T *string);
		String<T>& append(const T& character);
		String<T> subString(const uint& l, const uint& r) const;
		String<T>& operator=(const String<T>& anotherString);
		String<T> operator+(const T& character) const;
		String<T> operator+(const String<T>& anotherString) const;
		String<T>& operator+=(const String<T>& anotherString);
		bool operator==(const String<T>& anotherString) const;
		bool operator!=(const String<T>& anotherString) const;
		bool operator<(const String<T>& anotherString) const;
		bool operator<=(const String<T>& anotherString) const;
		bool operator>(const String<T>& anotherString) const;
		bool operator>=(const String<T>& anotherString) const;
		friend std::ostream& operator<<(std::ostream& os, const String<T>& str) {
			for (uint i = 0; i < str.size(); i++)
				os << str[i];
			return os;
		}
	};

	template<class T>
	String<T>::String() {
	}

	template<class T>
	String<T>::String(const T *string) {
		uint length = 0;
		for (length = 0; string[length]; length++);
		resize(length);
		for (uint i = 0; string[i]; i++)
			itemList[i] = string[i];
	}

	template<class T>
	inline String<T> String<T>::subString(const uint& l, const uint& r) const {
		String<T> resultString;
		for (uint i = l; i < r; i++) {
			resultString.append(itemList[i]);
		}
		return resultString;
	}
	
	template<class T>
	inline String<T>& String<T>::append(const T& character) {
		Array<T>::append(character);
		return *this;
	}

	template<class T>
	inline String<T>& String<T>::operator=(const String<T>& anotherString) {
		resize(anotherString.size());
		for (uint i = 0; i < anotherString.size(); i++) {
			itemList[i] = anotherString[i];
		}
		return *this;
	}

	template<class T>
	inline String<T> String<T>::operator+(const T& character) const {
		String result = *this;
		result.append(character);
		return result;
	}
	
	template<class T>
	inline String<T> operator+(const T& character, const String<T>& str) {
		String<T> result;
		result.resize(1);
		result[0] = character;
		return result += str;
	}

	template<class T>
	inline String<T> String<T>::operator+(const String<T>& anotherString) const {
		String<T> result;
		uint mySize = size(), anotherSize = anotherString.size();
		result.resize(mySize + anotherSize);
		for (uint i = 0; i < mySize; i++) {
			result[i] = itemList[i];
		}
		for (uint i = 0; i < anotherSize; i++) {
			result[i + mySize] = anotherString[i];
		}
		return result;
	}

	template<class T>
	inline String<T>& String<T>::operator+=(const String<T>& anotherString) {
		uint mySize = listSize, anotherSize = anotherString.size();
		uint newListSize = listSize + anotherSize;
		if (maxListSize < newListSize)
			setMaxSize(max(newListSize, maxListSize * factor));
		listSize = newListSize;
		for (uint i = 0; i < anotherSize; i++)
			itemList[i + mySize] = anotherString[i];
		return *this;
	}

	template<class T>
	inline bool String<T>::operator==(const String<T>& anotherString) const {
		if (size() != anotherString.size())
			return false;
		for (uint i = 0; i < size(); i++)
			if (itemList[i] != anotherString[i])
				return false;
		return true;
	}

	template<class T>
	inline bool String<T>::operator!=(const String<T>& anotherString) const {
		return !(operator==(anotherString));
	}

	template<class T>
	inline bool String<T>::operator<=(const String<T>& anotherString) const {
		for (uint i = 0; i < size() && i < anotherString.size(); i++) {
			if (itemList[i] != anotherString[i])
				return itemList[i] < anotherString[i];
		}
		return size() <= anotherString.size();
	}

	template<class T>
	inline bool String<T>::operator>(const String<T>& anotherString) const {
		return !(operator<=(anotherString));
	}

	template<class T>
	inline bool String<T>::operator<(const String<T>& anotherString) const {
		for (uint i = 0; i < size() && i < anotherString.size(); i++) {
			if (itemList[i] != anotherString[i])
				return itemList[i] < anotherString[i];
		}
		return size() < anotherString.size();
	}

	template<class T>
	inline bool String<T>::operator>=(const String<T>& anotherString) const {
		return !(operator<(anotherString));
	}

	template<class T>
	inline bool operator==(const T *literalString, const String<T>& anotherString) {
		return anotherString == literalString;
	}

	template<class T>
	bool operator!=(const T *literalString, const String<T>& anotherString) {
		return anotherString != literalString;
	}

	template<class T>
	bool operator<(const T *literalString, const String<T>& anotherString) {
		return anotherString > literalString;
	}

	template<class T>
	bool operator<=(const T *literalString, const String<T>& anotherString) {
		return anotherString >= literalString;
	}

	template<class T>
	bool operator>(const T *literalString, const String<T>& anotherString) {
		return anotherString < literalString;
	}

	template<class T>
	bool operator>=(const T *literalString, const String<T>& anotherString) {
		return anotherString <= literalString;
	}
}
