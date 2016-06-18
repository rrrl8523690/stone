#pragma once

namespace ds {

	template<class KeyType, class ValueType>
	class MapImpl {
	public:
		~MapImpl() {
		}
		//virtual void insert(const KeyType &key, const ValueType &value) = 0;
		virtual ValueType& find(const KeyType &key) = 0;
	};

	template<class KeyType, class ValueType>
	class TreeMapImpl;


	template<class KeyType, class ValueType, class MapImpl = TreeMapImpl<KeyType, ValueType> >
	class Map {
	public:
		Map() {
			m_mapImpl = new MapImpl();
		}
		~Map() {
			delete m_mapImpl;
		}
		ValueType& operator[](const KeyType &key) {
			return m_mapImpl->find(key);
		}
	private:
		MapImpl *m_mapImpl;
	};
}