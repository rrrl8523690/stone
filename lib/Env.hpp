#pragma once

#include "Data.hpp"
#include "String.hpp"
#include "common.h"

namespace stone {
	class Env : public Data {
	public:
		~Env() {
		}
		DataType type() const {
			return ENV;
		}
		virtual void put(const ds::String<char_type> &name, Data *data) = 0;
		virtual Data *&get(const ds::String<char_type> &name) = 0;
	};
}