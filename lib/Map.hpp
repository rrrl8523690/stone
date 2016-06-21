#pragma once

namespace ds {

	template<class KeyType, class ValueType>
	class MapImpl {
	public:
		~MapImpl() {
		}
		//virtual void insert(const KeyType &key, const ValueType &value) = 0;
		virtual const ValueType *get(const KeyType &key) = 0;
		virtual ValueType &getRef(const KeyType &key) = 0;
		virtual void put(const KeyType &key, const ValueType &value) = 0;
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
		ValueType &operator[](const KeyType &key) {
			return m_mapImpl->getRef(key);
		}
		const ValueType *get(const KeyType &key) {
			return m_mapImpl->get(key);
		}
		ValueType &getRef(const KeyType &key) {
			return m_mapImpl->getRef(key);
		}
		void put(const KeyType &key, const ValueType &value) {
			m_mapImpl->put(key, value);
		}
	private:
		MapImpl *m_mapImpl;
	};
}