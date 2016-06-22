#pragma once

#include <memory>

namespace ds {

	template<class KeyType, class ValueType>
	class MapImpl {
	public:
		using It = std::shared_ptr<ValueType>;
		~MapImpl() {
		}
		//virtual void insert(const KeyType &key, const ValueType &value) = 0;
		virtual It get(const KeyType &key) = 0;
		virtual It getOrCreate(const KeyType &key) = 0;
		virtual void put(const KeyType &key, const ValueType &value) = 0;
	};

	template<class KeyType, class ValueType>
	class TreeMapImpl;


	template<class KeyType, class ValueType, class MapImpl = TreeMapImpl<KeyType, ValueType> >
	class Map {
	public:
		using It = std::shared_ptr<ValueType>;
		Map() {
			m_mapImpl = new MapImpl();
		}
		~Map() {
			delete m_mapImpl;
		}
		ValueType &operator[](const KeyType &key) {
			return *m_mapImpl->getOrCreate(key);
		}
		It get(const KeyType &key) {
			return m_mapImpl->get(key);
		}
		It getOrCreate(const KeyType &key) {
			return m_mapImpl->getOrCreate(key);
		}
		void put(const KeyType &key, const ValueType &value) {
			m_mapImpl->put(key, value);
		}
	private:
		MapImpl *m_mapImpl;
	};
}