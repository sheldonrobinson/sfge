#include "sfge/graphics/light.hpp"
#include "sfge/math/point.hpp"
#include "sfge/math/vector_utilities.hpp"

#include <vector>
#include <iterator>

#include <boost/array.hpp>

using namespace std;
using namespace boost;
using namespace sf;

namespace sfge
{
	typedef vector<Edge2f> EdgeList;

	typedef Point<float, float> Pointf;
	typedef vector<Pointf> PointList;

	Light::Light()
		: mRadius(0.f), mShadowOutline(0, 0, 0, 0), mShadowFill(0, 0, 0, 255)
	{
	}

	Light::Light(const sf::Vector2f &pos, float rad)
		: mPos(pos), mRadius(rad), mShadowOutline(0, 0, 0, 0), mShadowFill(0, 0, 0, 255)
	{
	}

	void Light::DebugDraw(RenderTarget &target) const
	{
		if (mIsInside)
			return;

		target.Draw(Shape::Circle(mPos, mRadius, Color(150, 150, 30, 64)));
		target.Draw(Shape::Circle(mPos, 3, Color::Yellow));
	}

	void Light::reset()
	{
		swap(mShadows, Shadows());
		mIsInside = false;
	}

	void Light::addOccluders(const Shapes &occluders)
	{
		const sf::Vector2f scaledPos = mPos;

		Shapes _occluders(occluders);
		sort(_occluders.begin(), _occluders.end(),
			[&] (const ShapePtr &o1, const ShapePtr &o2) -> bool
			{
				const float	o1d = sqrDistance(o1->GetPosition(), scaledPos),
							o2d = sqrDistance(o2->GetPosition(), scaledPos);
				return o1d < o2d;
			} );

		Shapes::const_iterator it = _occluders.begin();
		while (it != _occluders.end() && addOccluder(*(*it)))
			++it;
	}

	bool Light::addOccluder(const Shape &occluder)
	{
#pragma region Setup
		if (mIsInside)
			return false;

		const unsigned int ptsCount = occluder.GetPointsCount();
		if (ptsCount < 2)
			return true;
#pragma endregion

		const sf::Vector2f	occLocalLPos	= occluder.TransformToLocal(mPos);
		const float		scaledRadius		= mRadius;
		const float		sqrRadius			= scaledRadius * scaledRadius;

		EdgeList edges;
		edges.reserve(ptsCount);
		PointList points;
		points.reserve(ptsCount);

#pragma region Generate occluder edges & store points
		for (unsigned int ptIdx = 0; ptIdx != ptsCount - 1; ptIdx++)
		{
			const Vector2f &pt1 = occluder.GetPointPosition(ptIdx);
			const Vector2f &pt2 = occluder.GetPointPosition(ptIdx + 1);
			edges.push_back(Edge2f(pt1, pt2));

			sf::Vector2f diff(occLocalLPos - pt1);
			points.push_back(Pointf(pt1, dot(diff, diff)));
		}
		const Vector2f &lastPoint = occluder.GetPointPosition(ptsCount - 1);
		edges.push_back(Edge2f(lastPoint, points[0].mPos, true));

		sf::Vector2f diff(occLocalLPos - lastPoint);
		points.push_back(Pointf(lastPoint, dot(diff, diff)));
#pragma endregion

#pragma region Check that occluder is at least partially within light radius
		int pointsWithinLightRad = 0;
		for (PointList::const_iterator it = points.begin(); it != points.end(); ++it)
		{
			pointsWithinLightRad += static_cast<int>(it->mUserVal < sqrRadius);

			if (pointsWithinLightRad > 1)
				break;
		}

		if (pointsWithinLightRad < 2)
			return false;
#pragma endregion
		
#pragma region Special case: simple line
		if (edges.size() == 1)
		{
			Edge2f globalEdge(occluder.TransformToGlobal(edges[0].v1), occluder.TransformToGlobal(edges[0].v2));
			generateShadowFromLine(edges[0]);
			return true;
		}
#pragma endregion
		
#pragma region Check if the light lies inside the occluder
		typedef vector<Edge2f::EdgeSide> EdgeSideList;
		EdgeSideList facing;
		facing.reserve(edges.size());
		transform(edges.begin(), edges.end(), back_inserter(facing),
			[&] (const Edge2f &e) -> Edge2f::EdgeSide { return e.checkSide(occLocalLPos); } );

		// And remove all edges which are facing the light
		EdgeSideList::const_iterator facingIt = facing.begin();
		const Edge2f::EdgeSide validSide = Edge2f::SideLeft;
		const size_t originalEdgesCount = edges.size();
		edges.erase(remove_if(edges.begin(), edges.end(),
							  [&] (const Edge2f &) -> bool
							  {
								  return (*facingIt++) != validSide;
							  } ),
					edges.end());

		mIsInside |= edges.size() == originalEdgesCount;
		if (mIsInside)
			return false;
#pragma endregion

#pragma region Generate occluding edge
		PointList occludingPoints;
		for_each(edges.begin(), edges.end(),
			[&] (Edge2f &e)
			{
				if (e.mClosePolygon)
					swap(e.v1, e.v2);

				occludingPoints.push_back(Pointf(e.v1, 0.5f));
				occludingPoints.push_back(Pointf(e.v2, 0.5f));
			} );

		// Add the light point to the points, in order to get the points that'll generate the occluding edge
		occludingPoints.push_back(Pointf(occLocalLPos, 1.f));

#pragma region Generate silhouette using Monotone chain
		
#pragma region Sort points based on angle from first point
		auto pointSorter = [&] (const Pointf &p1, const Pointf &p2) -> bool
							{ return p1.mPos.x < p2.mPos.x || (p1.mPos.x == p2.mPos.x && p1.mPos.y < p2.mPos.y) ; };
		sort(occludingPoints.begin(), occludingPoints.end(), pointSorter);
		occludingPoints.erase(unique(occludingPoints.begin(), occludingPoints.end()), occludingPoints.end());
#pragma endregion

		PointList hull(2 * occludingPoints.size());
		int k = 0;

#pragma region Build lower hull
		for (int i = 0; i != occludingPoints.size(); i++)
		{
			while (k >= 2 && cross(hull[k - 2].mPos, hull[k - 1].mPos, occludingPoints[i].mPos) <= 0)
				k--;
			hull[k++] = occludingPoints[i];
		}
#pragma endregion

#pragma region Build upper hull
		for (int i = occludingPoints.size() - 2, t = k + 1; i >= 0; i--)
		{
			while (k >= t && cross(hull[k - 2].mPos, hull[k - 1].mPos, occludingPoints[i].mPos) <= 0)
				k--;
			hull[k++] = occludingPoints[i];
		}
#pragma endregion

		hull.erase(remove_if(hull.begin(), hull.end(), [] (const Pointf &p) { return p.mUserVal < 0.1f; } ) - 1, hull.end());
		hull.shrink_to_fit();

#pragma endregion

		// And now that we have the convex hull, simply extract the points enclosing the light point.
		PointList::const_iterator lightPosIt = find_if(hull.begin(), hull.end(),
														[] (const Pointf &p) { return p.mUserVal > 0.9f; } );
		mIsInside = lightPosIt == hull.end();
		if (mIsInside)
			return false;

		PointList::const_iterator firstIt	= hull.begin();
		PointList::const_iterator lastIt	= hull.end() - 1;

		const Vector2f &v1 = lightPosIt == firstIt	? (*lastIt).mPos	: (*(lightPosIt - 1)).mPos;
		const Vector2f &v2 = lightPosIt == lastIt	? (*firstIt).mPos	: (*(lightPosIt + 1)).mPos;
		const Edge2f occludingEdge(v1, v2);

		Edge2f globalEdge(occluder.TransformToGlobal(occludingEdge.v1), occluder.TransformToGlobal(occludingEdge.v2));
		generateShadowFromLine(globalEdge);
#pragma endregion

		return true;
	}

	void Light::DrawShadows(RenderTarget &target) const
	{
		if (mIsInside)
			return;

		for_each(mShadows.begin(), mShadows.end(), [&] (const ShapePtr &shadow) { target.Draw(*shadow); } );
	}

	void Light::generateShadowFromLine(Edge2f &e)
	{
		const Vector2f	scaledPos		= mPos;
		const float		scaledRadius	= mRadius;
		const float		sqrScaledRadius	= scaledRadius * scaledRadius;

		// Clamp edge's endpoints to light radius
		Vector2f	lightToV1		= e.v1 - scaledPos,
					lightToV2		= e.v2 - scaledPos;
		const float	lightToV1Dist	= sqrLength(lightToV1),
					lightToV2Dist	= sqrLength(lightToV2);

		if (lightToV1Dist > sqrScaledRadius || lightToV2Dist > sqrScaledRadius)
		{
			const Vector2f	&edgeStartPoint	= e.v1;
			const Vector2f	 edgeDir		= e.v2 - edgeStartPoint;
			const float		 edgeDirSqrLen	= sqrLength(edgeDir);
			const Vector2f	 lightToStart	= edgeStartPoint - scaledPos;
			const float		 det			= pow(dot(edgeDir, lightToStart), 2) -
											  edgeDirSqrLen * (sqrLength(lightToStart) - sqrScaledRadius);
			if (det < epsilon<float>())
				return;

			const float	detRoot				= sqrt(det);
			const float	dDotDelta			= dot(-edgeDir, lightToStart);
			const float invEdgeDirSqrLen	= 1.f / edgeDirSqrLen;

			float t[2];
			t[0] = (dDotDelta - detRoot) * invEdgeDirSqrLen;
			t[1] = (dDotDelta + detRoot) * invEdgeDirSqrLen;

			if (t[0] > epsilon<float>() && t[0] < 1.f)
				e.v1 = edgeStartPoint + t[0] * edgeDir;
			if (t[1] > epsilon<float>() && t[1] < 1.f)
				e.v2 = edgeStartPoint + t[1] * edgeDir;
		}
		
		// Generate 6 additionnal points to be the shadow's endpoints
		// FIXME adaptive tessellation w/r <angle,dist> needed!
		const int endPointsCount = 6;
		const float invSplit = 1.f / (endPointsCount - 1);
		array<Vector2f, endPointsCount> endPoints;
		const Vector2f delta(e.v2 - e.v1);

		endPoints[0]					= e.v1;
		endPoints[endPointsCount - 1]	= e.v2;

		for (size_t i = 1; i != endPoints.size() - 1; i++)
		{
			const float splitFactor	= invSplit * i;
			endPoints[i]			= delta * splitFactor  + e.v1;
		}

		// Compute extrusion distance (from midpoint to be sure to stay within light's radius
		for (size_t i = 0; i != endPoints.size(); i++)
		{
			Vector2f diff			= endPoints[i] - scaledPos;
			const float extrudeLen	= scaledRadius - length(diff) + 1.f;

			normalize(diff);
			endPoints[i] += diff * extrudeLen;
		}

		ShapePtr shadow(new Shape);
		shadow->AddPoint(e.v1, mShadowFill, mShadowOutline);

		for_each(endPoints.begin(), endPoints.end(),
			[&] (const Vector2f &v)
			{
				sf::Color endShadowFill(mShadowFill);
				endShadowFill.a = static_cast<Uint8>(endShadowFill.a * 0.25f);
				shadow->AddPoint(v, endShadowFill, mShadowOutline);
			} );
		shadow->AddPoint(e.v2, mShadowFill, mShadowOutline);
		shadow->SetOutlineThickness(1.f);
		
		mShadows.push_back(shadow);
	}
}
