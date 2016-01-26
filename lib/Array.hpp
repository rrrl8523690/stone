#pragma once

#include "stdafx.h"
#include <iostream>

namespace ds {
	template<class T>
	class Array {
	public:
		Array();
		Array(const Array<T>& anotherArray);
		Array(const uint& intialSize);
		Array(T fromArray[], const uint& arraySize);
		~Array();
		uint size() const;
		void resize(const uint& newSize);
		void setMaxSize(const uint& newMaxSize);
		T& at(const uint& index);
		Array<T>& append(const T& item);
		Array<T>& clear();

		friend std::ostream& operator<<(std::ostream& os, const Array<T>& arr) {
			os << "{";
			for (uint i = 0; i < arr.size(); i++) {
				if (i) os << ", ";
				os << arr[i];
			}
			os << "}";
			return os;
		}
		T& operator[](const uint& index);
		const T &operator[](const uint& index) const;
		Array<T> operator+(const Array<T>& anotherArray) const;
		Array<T>& operator+=(const Array<T>& anotherArray);
		Array<T>& operator=(const Array<T>& anotherArray);
		bool operator==(const Array<T>& anotherArray) const;
		bool operator!=(const Array<T>& anotherArray) const;

	protected:
		static const uint factor = 2;
		T *itemList;
		uint maxListSize, listSize;
	};

	template<class T>
	Array<T>::Array() {
		maxListSize = 0;
		listSize = 0;
		itemList = nullptr;
	}

	template<class T>
	Array<T>::Array(const Array<T>& anotherArray) {
		itemList = nullptr;
		listSize = 0;
		resize(anotherArray.size());
		for (uint i = 0; i < listSize; i++)
			itemList[i] = anotherArray[i];
	}

	template<class T>
	Array<T>::Array(const uint& initialSize) {
		maxListSize = initialSize;
		listSize = 0;
		itemList = nullptr;
		resize(maxListSize);
	}

	template<class T>
	Array<T>::Array(T fromArray[], const uint& arraySize) {
		itemList = nullptr;
		listSize = 0;
		resize(arraySize);
		for (uint i = 0; i < size(); i++)
			itemList[i] = fromArray[i];
	}

	template<class T>
	Array<T>::~Array() {
		delete[] itemList;
	}

	template<class T>
	inline uint Array<T>::size() const {
		return listSize;
	}

	template<class T>
	inline void Array<T>::resize(const uint& newSize) {
		T *newItemList = new T[newSize];
		for (uint i = 0; i < listSize && i < newSize; i++) {
			newItemList[i] = itemList[i];
		}
		listSize = newSize;
		maxListSize = newSize;
		delete[] itemList;
		itemList = newItemList;
	}

	template<class T>
	inline void Array<T>::setMaxSize(const uint& newMaxSize) {
		T *newItemList = new T[newMaxSize];
		for (uint i = 0; i < listSize && i < newMaxSize; i++) {
			newItemList[i] = itemList[i];
		}
		listSize = min(listSize, newMaxSize);
		maxListSize = newMaxSize;
		delete[] itemList;
		itemList = newItemList;
	}

	template<class T>
	inline T& Array<T>::at(const uint& index) {
		return itemList[index];
	}

	template<class T>
	inline Array<T>& Array<T>::append(const T& item) {
		if (listSize == maxListSize) {
			setMaxSize(max(maxListSize * factor, maxListSize + 1));
		}
		itemList[listSize++] = item;
		return *this;
	}

	template<class T>
	inline Array<T>& Array<T>::clear() {
		resize(0);
		return *this;
	}

	template<class T>
	inline T& Array<T>::operator[](const uint& index) {
		return itemList[index];
	}

	template<class T>
	inline const T& Array<T>::operator[](const uint& index) const {
		return itemList[index];
	}

	template<class T>
	inline Array<T> Array<T>::operator+(const Array<T>& anotherArray) const {
		Array<T> resultArray;
		uint mySize = listSize, anotherSize = anotherArray.size();
		resultArray.resize(mySize + anotherSize);
		for (uint i = 0; i < mySize; i++)
			resultArray[i] = itemList[i];
		for (uint i = 0; i < anotherSize; i++)
			resultArray[i + mySize] = anotherArray[i];
		return resultArray;
	}

	template<class T>
	inline Array<T>& Array<T>::operator+=(const Array<T>& anotherArray) {
		uint mySize = listSize, anotherSize = anotherArray.size();
		resize(listSize + anotherArray.listSize);
		for (uint i = 0; i < anotherSize; i++)
			itemList[i + mySize] = anotherArray[i];
		return *this;
	}

	template<class T>
	inline Array<T>& Array<T>::operator=(const Array<T>& anotherArray) {
		resize(anotherArray.size());
		for (uint i = 0; i < anotherArray.size(); i++)
			itemList[i] = anotherArray[i];
		return *this;
	}

	template<class T>
	inline bool Array<T>::operator==(const Array<T>& anotherArray) const {
		if (listSize != anotherArray.listSize)
			return false;
		for (uint i = 0; i < listSize; i++) {
			if (itemList[i] != anotherArray[i])
				return false;
		}
		return true;
	}

	template<class T>
	inline bool Array<T>::operator!=(const Array<T>& anotherArray) const {
		return !(this->operator==(anotherArray));
	}
}


