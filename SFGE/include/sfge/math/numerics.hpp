#ifndef SFGE_MATH_NUMERICS_HPP
#define SFGE_MATH_NUMERICS_HPP

#include <limits>

namespace sfge
{
	//! Simply a shorthand to std::numeric_limits::epsilon.
	template <typename T>
	inline T epsilon();

	//! Equality testing for fp values. Not as solid as the algorithm from boost.units, but not as costly.
	template <typename RealT>
	inline bool realEqual(RealT x, RealT y);

#include "numerics.inl"
}

#endif
