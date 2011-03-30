#ifndef SFGE_MATH_POINT_HPP
#define SFGE_MATH_POINT_HPP

#include "sfge/math/vector_utilities.hpp"

namespace sfge
{
	template <typename VectorStorageT, typename UserValT>
	struct Point
	{
		typedef sf::Vector2<VectorStorageT> vector_type;

		Point()														{ ; }
		explicit Point(const vector_type &pos) : mPos(pos)			{ ; }
		Point(const vector_type &pos, UserValT userVal)
			: mPos(pos), mUserVal(userVal)
		{
		}

		vector_type		mPos;
		UserValT		mUserVal;
	};

	template <typename VectorStorageT>
	struct Point<VectorStorageT, void>
	{
		typedef sf::Vector2<VectorStorageT> vector_type;

		Point()												{ ; }
		explicit Point(const vector_type &pos) : mPos(pos)	{ ; }

		vector_type		mPos;
	};
	
	template <typename VectorStorageT, typename UserValT>
	inline bool operator<(const Point<VectorStorageT, UserValT> &p1, const Point<VectorStorageT, UserValT> &p2);
	
	template <typename VectorStorageT, typename UserValT>
	bool operator==(const Point<VectorStorageT, UserValT> &p1, const Point<VectorStorageT, UserValT> &p2);

#include "point.inl"
}

#endif
