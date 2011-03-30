#ifndef SFGE_MATH_INTERSECTIONS_HPP
#define SFGE_MATH_INTERSECTIONS_HPP

#include <boost/array.hpp>

#include <SFML/System/Vector2.hpp>

#include "sfge/math/circle.hpp"
#include "sfge/math/edge.hpp"
#include "sfge/math/numerics.hpp"

namespace sfge
{
	enum IntersectionResult
	{
		IR_None,
		IR_Tangent,
		IR_TwoIntersections
	};
	
	template <typename VectorStorageT>
	struct EdgeCircleIntersectionCont
	{
		boost::array<VectorStorageT, 2> mTs;
		sf::Vector2f					mStartPoint;
		sf::Vector2f					mDir;
	};
	
	template <typename VectorStorageT>
	IntersectionResult	intersect(const Edge2<VectorStorageT> &e, const Circle<VectorStorageT> &c,
								  EdgeCircleIntersectionCont<VectorStorageT> &out);

#include "intersections.inl"
}

#endif
