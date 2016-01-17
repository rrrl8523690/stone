#pragma once

#include "stdafx.h"

namespace ds {
	template<class T>
	class Array {
	public:
		Array();
		Array(const uint& intialSize);
		~Array();
		uint size();
		void resize(const uint& newSize);
		T& at(const uint& index);
		Array<T>& append(const T& item);
		Array<T>& clear();

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
	Array<T>::Array(const uint& initialSize) {
		maxListSize = initialSize;
		listSize = 0;
		itemList = nullptr;
		resize(maxListSize);
	}

	template<class T>
	Array<T>::~Array() {
		delete[] itemList;
	}

	template<class T>
	inline uint Array<T>::size() {
		return listSize;
	}

	template<class T>
	inline void Array<T>::resize(const uint& newSize) {
		T *newItemList = new T[newSize];
		for (uint i = 0; i < listSize && i < newSize; i++) {
			newItemList[i] = itemList[i];
		}
		listSize = min(listSize, newSize);
		maxListSize = newSize;
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
			resize(max(maxListSize * factor, maxListSize + 1));
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
		resultArray.resize(listSize + anotherArray.listSize);
		for (uint i = 0; i < listSize; i++)
			resultArray[i] = itemList[i];
		for (uint i = 0; i < anotherArray.listSize; i++)
			resultArray[i + listSize] = anotherArray[i];
		return resultArray;
	}

	template<class T>
	inline Array<T>& Array<T>::operator+=(const Array<T>& anotherArray) {
		resize(listSize + anotherArray.listSize);
		for (uint i = 0; i < anotherArray.listSize; i++)
			itemList[i + listSize] = anotherArray[i];
		return *this;
	}

	template<class T>
	inline Array<T>& Array<T>::operator=(const Array<T>& anotherArray) {
		resize(anotherArray.size());
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


