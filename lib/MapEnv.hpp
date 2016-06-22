#pragma once

#include "Map.hpp"
#include "Env.hpp"
#include "String.hpp"
#include <memory>

namespace stone {
	class MapEnv : public virtual Env {
	public:
		using MapEnvPtr = std::shared_ptr<MapEnv>;
		MapEnv(MapEnvPtr outer_, MapEnvPtr parent_)
			: m_map(new ds::Map<ds::String<char_type>, std::shared_ptr<Data> >()) {
			m_outer = outer_;
			m_parent = parent_;
		}
		MapIt get(const ds::String<char_type> &name) { // get Data for value
			MapIt result = m_map->get(name);
			if (result)
				return result;
			MapEnvPtr ptr;
			for (ptr = m_outer; ptr; ptr = ptr->m_outer) {
				result = ptr->m_map->get(name);
				if (result)
					return result;
			}
			return nullptr;
		}
		MapIt getOrCreate(const ds::String<char_type> &name) { // get pointer to Data's position, if it doesn't have one, create it in the current scope
			MapIt result = m_map->get(name);
			MapEnvPtr ptr;
			for (ptr = m_outer; !result && ptr; ptr = ptr->m_outer) {
				result = ptr->m_map->get(name);
			}
			if (result) {
				return result;
			} else {
				return m_map->getOrCreate(name);
			}
		}
	private:
		std::shared_ptr<ds::Map<ds::String<char_type>, std::shared_ptr<Data> > > m_map;
		MapEnvPtr m_outer, m_parent;
	};
}