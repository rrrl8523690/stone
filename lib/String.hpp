#pragma once

#include "Array.hpp"

namespace ds {
	template<class T = char>
	class String : public Array<T> {
	public:
		String(const T *string);
		String<T> subString(const uint& l, const uint& r) const;
		bool operator<(const String<T>& anotherString) const;
		bool operator<=(const String<T>& anotherString) const;
		bool operator>(const String<T>& anotherString) const;
		bool operator>=(const String<T>& anotherString) const;
	};

	template<class T>
	String<T>::String(const T *string) {
		uint length = 0;
		for (length = 0; string[length]; length++);
		resize(length);
		for (uint i = 0; string[i]; i++)
			itemList[i] = string[i];
	}

	template<class T>
	String<T> String<T>::subString(const uint& l, const uint& r) const {
		String<T> resultString;
		for (uint i = l; i < r; i++) {
			resultString.append(itemList[i]);
		}
		return resultString;
	}

	template<class T>
	bool String<T>::operator<(const String<T>& anotherString) const {
		for (uint i = 0; i < size() && i < anotherString.size(); i++) {
			if (itemList[i] != anotherString[i])
				return itemList[i] < anotherString[i];
		}
		return size() < anotherString.size();
	}

	template<class T>
	bool String<T>::operator<=(const String<T>& anotherString) const {
		for (uint i = 0; i < size() && i < anotherString.size(); i++) {
			if (itemList[i] != anotherString[i])
				return itemList[i] < anotherString[i];
		}
		return size() <= anotherString.size();
	}

	template<class T>
	bool String<T>::operator>(const String<T>& anotherString) const {
		for (uint i = 0; i < size() && i < anotherString.size(); i++) {
			if (itemList[i] != anotherString[i])
				return itemList[i] > anotherString[i];
		}
		return size() > anotherString.size();
	}

	template<class T>
	bool String<T>::operator>=(const String<T>& anotherString) const {
		for (uint i = 0; i < size() && i < anotherString.size(); i++) {
			if (itemList[i] != anotherString[i])
				return itemList[i] > anotherString[i];
		}
		return size() >= anotherString.size();
	}
}