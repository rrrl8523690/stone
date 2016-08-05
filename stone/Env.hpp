#pragma once

#include "Data.hpp"
#include "../ds/String.hpp"
#include "../main/common.h"
#include "../ds/Map.hpp"
#include <memory>

namespace stone {
	class Env : public Data {
	public:
		using DataPtr = std::shared_ptr<std::shared_ptr<Data> >;
		using EnvPtr = std::shared_ptr<Env>;
		virtual ~Env() {
		}
		DataType type() const {
			return ENV;
		}
		virtual DataPtr get(const ds::String<char_type> &name) = 0;
		virtual DataPtr getOrCreate(const ds::String<char_type> &name) = 0;
		EnvPtr &outer() {
			return m_outer;
		}
		EnvPtr &parent() {
			return m_parent;
		}
		virtual DataPtr getInCurrentEnv(const ds::String<char_type> &name) = 0;
	private:
		EnvPtr m_outer, m_parent;
	};
}