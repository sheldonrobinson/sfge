template <typename PointT>
ConvexHull<PointT>::ConvexHull()
{
}

template <typename PointT>
void ConvexHull<PointT>::addPoint(const PointT &point)
{
	mInitialPoints.push_back(point);
}

template <typename PointT>
void ConvexHull<PointT>::build(const PointT &defaultPoint)
{
	// Sort points based on angle from first point
	auto pointSorter = [&] (const PointT &p1, const PointT &p2) -> bool
						{ return p1.mPos.x < p2.mPos.x || (realEqual(p1.mPos.x, p2.mPos.x) && p1.mPos.y < p2.mPos.y) ; };
	sort(mInitialPoints.begin(), mInitialPoints.end(), pointSorter);
	mInitialPoints.erase(unique(mInitialPoints.begin(), mInitialPoints.end()), mInitialPoints.end());

	mHullPoints.swap(HullPoints());
	mHullPoints.resize(2 * mInitialPoints.size(), defaultPoint);
	int k = 0;

	// Build lower hull
	for (int i = 0; i != mInitialPoints.size(); i++)
	{
		while (k >= 2 && cross(mHullPoints[k - 2].mPos, mHullPoints[k - 1].mPos, mInitialPoints[i].mPos) <= 0)
			k--;
		mHullPoints[k++] = mInitialPoints[i];
	}

	// Build upper hull
	for (int i = mInitialPoints.size() - 2, t = k + 1; i >= 0; i--)
	{
		while (k >= t && cross(mHullPoints[k - 2].mPos, mHullPoints[k - 1].mPos, mInitialPoints[i].mPos) <= 0)
			k--;
		mHullPoints[k++] = mInitialPoints[i];
	}
}

template <typename PointT>
template <typename Pred>
void ConvexHull<PointT>::clean(Pred cleaner)
{
	mHullPoints.erase(remove_if(mHullPoints.begin(), mHullPoints.end(), cleaner) - 1, mHullPoints.end());
	mHullPoints.shrink_to_fit();
}

template <typename PointT>
typename const ConvexHull<PointT>::HullPoints& ConvexHull<PointT>::get() const
{
	return mHullPoints;
}
