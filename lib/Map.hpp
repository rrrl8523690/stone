#pragma once

namespace ds {
	template<class KeyType, class ValueType>
	class TreeMapImpl;

	template<class KeyType, class ValueType, class MapImpl = TreeMapImpl<KeyType, ValueType> >
	class Map {
	public:
		void set(const KeyType &key, const ValueType &value);
		ValueType get(const KeyType &key);
		ValueType& operator[](const KeyType &key);
	};
}