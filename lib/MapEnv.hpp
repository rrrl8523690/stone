#pragma once

#include "Map.hpp"
#include "Env.hpp"
#include "String.hpp"

namespace stone {
	class MapEnv : public virtual Env {
	public:
		MapEnv(MapEnv *outer_, MapEnv *parent_) {
			m_outer = outer_;
			m_parent = parent_;
			m_map = new ds::Map<ds::String<char_type>, Data*>();
		}
		void put(const ds::String<char_type> &name, Data *data) {
			if ()
		}
	private:
		ds::Map<ds::String<char_type>, Data*> *m_map;
		MapEnv *m_outer, *m_parent;
	};
}