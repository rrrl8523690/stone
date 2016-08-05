#pragma once

#include "ds/AutoComparable.hpp"
#include "common/Common.h"
#include <iostream>
#include <initializer_list>

namespace ds {
    template<class T>
    class ArrayIterator;

    template<class T>
    class Array : public virtual AutoComparable<Array<T>> {
    public:
        Array();

        Array(const Array<T> &anotherArray);

        Array(Array<T> &&anotherArray);

        explicit Array(const uint &intialSize);

        Array(const std::initializer_list<T> &literalArray);

        explicit Array(const T fromArray[], const uint &arraySize);

        ~Array();

        uint size() const;

        bool empty() const;

        void resize(const uint &newSize);

        void setMaxSize(const uint &newMaxSize);

        T &at(const uint &index);

        void append(const T &item);

        void clear();


        T &operator[](const uint &index);

        const T &operator[](const uint &index) const;

        Array<T> operator+(const Array<T> &anotherArray) const;

        Array<T> &operator+=(const Array<T> &anotherArray);

        Array<T> &operator=(const Array<T> &anotherArray);

        Array<T> &operator=(Array<T> &&anotherArray);

        bool operator<(const Array<T> &anotherArray) const {
            for (uint i = 0; i < this->m_size && i < anotherArray.m_size; i++) {
                if (m_items[i] != anotherArray.m_items[i]) {
                    return m_items[i] < anotherArray.m_items[i];
                }
            }
            return m_size < anotherArray.m_size;
        }

    protected:
        static const uint m_factor = 2;
        T *m_items;
        uint m_maxSize, m_size;

        inline void initialize();

    private:
        inline void helpMove(Array<T> &&anotherArray) {
            if (this != &anotherArray) {
                delete[] m_items;
                m_items = anotherArray.m_items;
                m_size = anotherArray.m_size;
                m_maxSize = anotherArray.m_maxSize;
                anotherArray.m_size = 0;
                anotherArray.m_maxSize = 0;
                anotherArray.m_items = nullptr;
            }
        }
    };


    template<class T>
    std::ostream &operator<<(std::ostream &os, const Array<T> &arr) {
        os << "{";
        for (uint i = 0; i < arr.size(); i++) {
            if (i) os << ", ";
            os << arr[i];
        }
        os << "}";
        return os;
    }

    template<class T>
    Array<T>::Array() {
        initialize();
    }

    template<class T>
    Array<T>::Array(const Array<T> &anotherArray) {
        initialize();
        resize(anotherArray.size());
        for (uint i = 0; i < m_size; i++)
            m_items[i] = anotherArray[i];
    }

    template<class T>
    Array<T>::Array(Array<T> &&anotherArray) {
        initialize();
        helpMove(std::move(anotherArray));
    }

    template<class T>
    Array<T>::Array(const uint &initialSize) {
        initialize();
        m_maxSize = initialSize;
        resize(m_maxSize);
    }

    template<class T>
    Array<T>::Array(const std::initializer_list<T> &literalArray) {
        initialize();
        for (const auto &item : literalArray) {
            append(item);
        }
    }

    template<class T>
    Array<T>::Array(const T fromArray[], const uint &arraySize) {
        initialize();
        resize(arraySize);
        for (uint i = 0; i < size(); i++)
            m_items[i] = fromArray[i];
    }

    template<class T>
    Array<T>::~Array() {
        delete[] m_items;
    }

    template<class T>
    inline uint Array<T>::size() const {
        return m_size;
    }

    template<class T>
    inline bool Array<T>::empty() const {
        return !m_size;
    }

    template<class T>
    inline void Array<T>::resize(const uint &newSize) {
        if (newSize <= m_maxSize) {
            m_size = newSize;
            return;
        }
        T *newItemList = new T[newSize];
        for (uint i = 0; i < m_size && i < newSize; i++) {
            newItemList[i] = m_items[i];
        }
        m_size = newSize;
        m_maxSize = newSize;
        delete[] m_items;
        m_items = newItemList;
    }

    template<class T>
    inline void Array<T>::setMaxSize(const uint &newMaxSize) {
        if (m_maxSize == newMaxSize)
            return;
        T *newItemList = new T[newMaxSize];
        for (uint i = 0; i < m_size && i < newMaxSize; i++) {
            newItemList[i] = m_items[i];
        }
        m_size = min(m_size, newMaxSize);
        m_maxSize = newMaxSize;
        delete[] m_items;
        m_items = newItemList;
    }

    template<class T>
    inline T &Array<T>::at(const uint &index) {
        return m_items[index];
    }

    template<class T>
    inline void Array<T>::append(const T &item) {
        if (m_size == m_maxSize) {
            setMaxSize(max(m_maxSize * m_factor, m_maxSize + 1));
        }
        m_items[m_size++] = item;
    }

    template<class T>
    inline void Array<T>::clear() {
        resize(0);
    }

    template<class T>
    inline T &Array<T>::operator[](const uint &index) {
        return m_items[index];
    }

    template<class T>
    inline const T &Array<T>::operator[](const uint &index) const {
        return m_items[index];
    }

    template<class T>
    inline Array<T> Array<T>::operator+(const Array<T> &anotherArray) const {
        Array<T> resultArray;
        uint mySize = m_size, anotherSize = anotherArray.size();
        resultArray.resize(mySize + anotherSize);
        for (uint i = 0; i < mySize; i++)
            resultArray[i] = m_items[i];
        for (uint i = 0; i < anotherSize; i++)
            resultArray[i + mySize] = anotherArray[i];
        return resultArray;
    }

    template<class T>
    inline Array<T> &Array<T>::operator+=(const Array<T> &anotherArray) {
        uint mySize = m_size, anotherSize = anotherArray.size();
        uint newListSize = m_size + anotherSize;
        if (m_maxSize < newListSize)
            setMaxSize(max(newListSize, m_maxSize * m_factor));
        m_size = newListSize;
        for (uint i = 0; i < anotherSize; i++)
            m_items[i + mySize] = anotherArray[i];
        return *this;
    }

    template<class T>
    inline Array<T> &Array<T>::operator=(const Array<T> &anotherArray) {
        resize(anotherArray.size());
        for (uint i = 0; i < anotherArray.size(); i++)
            m_items[i] = anotherArray[i];
        return *this;
    }

    template<class T>
    inline Array<T> &Array<T>::operator=(Array<T> &&anotherArray) {
        helpMove(std::move(anotherArray));
        return *this;
    }

//
//    template<class T>
//    inline bool Array<T>::operator!=(const Array<T> &anotherArray) const {
//        return !(operator==(anotherArray));
//    }

    template<class T>
    inline void Array<T>::initialize() {
        m_items = nullptr;
        m_size = 0;
        m_maxSize = 0;
    }

}

