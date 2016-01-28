#pragma once

#include "String.hpp"

namespace re {
	using namespace ds;

	template<class CharType = char>
	class RegExpReader {
	public:
		RegExpReader(const String<CharType>& _reString) {
			reString = _reString;
			pos = 0;
		}

		CharType read() const {
			return reString[pos++];
		}

		bool hasNext(const uint& step = 0) const {
			return pos + step < reString.size();
		}

		CharType peek(const uint& step = 0) const {
			return reString[pos + step];
		}

	private:
		uint pos;
		String<CharType> reString;
	};
}