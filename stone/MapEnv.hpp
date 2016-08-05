#pragma once

#include "ds/Map.hpp"
#include "stone/Env.hpp"
#include "ds/String.hpp"
#include <memory>

namespace stone {
	class MapEnv : public virtual Env {
	public:
		MapEnv(EnvPtr outer_, EnvPtr parent_)
			: m_map(new ds::Map<ds::String<char_type>, std::shared_ptr<Data> >()) {
			outer() = outer_;
			parent() = parent_;
		}
		DataPtr get(const ds::String<char_type> &name) { // get Data for value
			DataPtr result = getInCurrentEnv(name);
			if (result)
				return result;
			EnvPtr ptr;
			for (ptr = outer(); ptr; ptr = ptr->outer()) {
				result = ptr->getInCurrentEnv(name);
				if (result)
					return result;
			}
			return nullptr;
		}
		DataPtr getOrCreate(const ds::String<char_type> &name) { // get pointer to Data's position, if it doesn't have one, create it in the current scope
			DataPtr result = getInCurrentEnv(name);
			EnvPtr ptr;
			for (ptr = outer(); !result && ptr; ptr = ptr->outer()) {
				result = ptr->getInCurrentEnv(name);
			}
			if (result) {
				return result;
			} else {
				return m_map->getOrCreate(name);
			}
		}
	protected:
		DataPtr getInCurrentEnv(const ds::String<char_type> &name) {
			return m_map->get(name);
		}
	private:
		std::shared_ptr<ds::Map<ds::String<char_type>, std::shared_ptr<Data> > > m_map;
	};
}