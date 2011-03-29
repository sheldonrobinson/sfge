#ifndef SFGE_MATH_CONVEX_HULL_HPP
#define SFGE_MATH_CONVEX_HULL_HPP

#include <algorithm>
#include <vector>

namespace sfge
{
	template <typename PointT>
	class ConvexHull
	{
	public:
		typedef std::vector<PointT> HullPoints;

	public:
		ConvexHull();

		void				addPoint(const PointT &point);
		void				build(const PointT &defaultPoint);
		template <typename Pred>
		void				clean(Pred cleaner);
		const HullPoints&	get() const;

	private:
		HullPoints	mInitialPoints;
		HullPoints	mHullPoints;
	};

#include "convex_hull.inl"
}

#endif
