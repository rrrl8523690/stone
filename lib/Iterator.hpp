#pragma once

namespace ds {
	template<class iterator>
	struct iterator_traits {
		typedef typename iterator::category category;
		typedef typename iterator::value_type value_type;
		typedef typename iterator::pointer pointer;
		typedef typename iterator::ref ref;
	};

	
}