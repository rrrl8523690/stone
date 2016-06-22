#pragma once

#include "Data.hpp"
#include "String.hpp"
#include "common.h"
#include "Map.hpp"
#include <memory>

namespace stone {
	class Env : public Data {
	public:
		using MapIt = ds::Map<ds::String<char_type>, std::shared_ptr<Data> >::It;
		virtual ~Env() {
		}
		DataType type() const {
			return ENV;
		}
		virtual MapIt get(const ds::String<char_type> &name) = 0;
		virtual MapIt getOrCreate(const ds::String<char_type> &name) = 0;
	};
}