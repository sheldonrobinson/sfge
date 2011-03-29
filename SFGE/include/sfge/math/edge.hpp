#ifndef SFGE_MATH_EDGE_HPP
#define SFGE_MATH_EDGE_HPP

#include <SFML/System/Vector2.hpp>

#include "sfge/math/numerics.hpp"

namespace sfge
{
	template <typename VectorStorageT>
	struct Edge2
	{
		typedef sf::Vector2<VectorStorageT> vector_type;

		enum EdgeSide
		{
			SideRight,
			SideLie,
			SideLeft,
		};

		Edge2()																{ ; }
		Edge2(const Edge2 &other) : v1(other.v1), v2(other.v2)				{ ; }
		Edge2(const vector_type &_1, const vector_type &_2, bool closingPolygon = false)
			: v1(_1), v2(_2), mClosePolygon(closingPolygon)
		{
		}

		EdgeSide checkSide(const vector_type &pt) const;

		vector_type		v1, v2;
		bool			mClosePolygon;
	};

	typedef Edge2<float> Edge2f;

#include "edge.inl"
}

#endif
