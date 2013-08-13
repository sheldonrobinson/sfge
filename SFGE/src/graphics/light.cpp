#include "sfge/graphics/light.hpp"
#include "sfge/math/convex_hull.hpp"
#include "sfge/math/intersections.hpp"
#include "sfge/math/point.hpp"
#include "sfge/math/vector_utilities.hpp"

#include <vector>
#include <iterator>

#include <boost/array.hpp>

#include <SFML/Graphics/ConvexShape.hpp>

#include <sfge/math/circle.hpp>

using namespace std;
using namespace boost;
using namespace sf;

namespace sfge
{

typedef vector<Edge2f> EdgeList;

typedef Point<float, float> Pointf;
typedef vector<Pointf> PointfList;

typedef Point<float, int> PointInt;
typedef vector<PointInt> PointIntList;

typedef ConvexHull<PointInt> ConvexHullT;

Light::Light()
	: mShadowOutline(0, 0, 0, 0), mShadowFill(0, 0, 0, 255)
{
}

Light::Light(const sf::Vector2f &pos, float rad)
	: mLightDesc(pos, rad), mShadowOutline(0, 0, 0, 0), mShadowFill(0, 0, 0, 255)
{
}

void Light::reset()
{
	swap(mShadows, Shadows());
	mIsInside = false;
}

void Light::addOccluders(const Shapes &occluders)
{
	Shapes _occluders(occluders);
	sort(_occluders.begin(), _occluders.end(),
		[&] (const ShapePtr &o1, const ShapePtr &o2) -> bool
		{
			const float	o1d = sqrDistance(o1->getPosition(), mLightDesc.mPos),
						o2d = sqrDistance(o2->getPosition(), mLightDesc.mPos);
			return o1d < o2d;
		} );

	Shapes::const_iterator it = _occluders.begin();
	while (it != _occluders.end() && addOccluder(*(*it)))
		++it;
}

bool Light::addOccluder(const Shape &occluder)
{
	// Setup
	if (mIsInside)
		return false;

	const unsigned int ptsCount = occluder.getPointCount();
	if (ptsCount < 2)
		return true;

	const sf::Vector2f	occLocalLPos	= occluder.getInverseTransform().transformPoint(mLightDesc.mPos);
	const float		scaledRadius		= mLightDesc.mRadius;
	const float		sqrRadius			= scaledRadius * scaledRadius;

	EdgeList edges;
	edges.reserve(ptsCount);
	PointfList points;
	points.reserve(ptsCount);

	// Generate occluder's edges & store points
	for (unsigned int ptIdx = 0; ptIdx != ptsCount - 1; ptIdx++)
	{
		const Vector2f &pt1 = occluder.getPoint(ptIdx);
		const Vector2f &pt2 = occluder.getPoint(ptIdx + 1);
		edges.push_back(Edge2f(pt1, pt2));

		sf::Vector2f diff(occLocalLPos - pt1);
		points.push_back(Pointf(pt1, dot(diff, diff)));
	}
	const Vector2f &lastPoint = occluder.getPoint(ptsCount - 1);
	edges.push_back(Edge2f(lastPoint, points[0].mPos, true));

	sf::Vector2f diff(occLocalLPos - lastPoint);
	points.push_back(Pointf(lastPoint, dot(diff, diff)));

	// Check that occluder is at least partially within light radius
	int pointsWithinLightRad = 0;
	for (PointfList::const_iterator it = points.begin(); it != points.end(); ++it)
	{
		pointsWithinLightRad += static_cast<int>(it->mUserVal < sqrRadius);

		if (pointsWithinLightRad > 1)
			break;
	}

	if (pointsWithinLightRad < 2)
		return false;
		
	// Special case: simple line, no need to think long
	if (edges.size() == 1)
	{
		Edge2f globalEdge(occluder.getTransform().transformPoint(edges[0].v1), occluder.getTransform().transformPoint(edges[0].v2));
		generateShadowFromLine(edges[0]);
		return true;
	}
		
	// Check if the light lies inside the occluder
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

	// Generate occluding edge
	static const int NullPointTag	= 0;
	static const int HullPointTag	= 1;
	static const int LightPointTag	= 2;

	ConvexHullT hull;

	PointIntList occludingPoints;
	for_each(edges.begin(), edges.end(),
		[&] (Edge2f &e)
		{
			if (e.mClosePolygon)
				swap(e.v1, e.v2);

			hull.addPoint(PointInt(e.v1, HullPointTag));
			hull.addPoint(PointInt(e.v2, HullPointTag));
		} );

	// Add the light point to the points, in order to get the points that'll generate the occluding edge
	hull.addPoint(PointInt(occLocalLPos, LightPointTag));
	hull.build(PointInt(Vector2f(), NullPointTag));
	hull.clean( [] (const PointInt &p) { return p.mUserVal == NullPointTag; } );
	const ConvexHullT::HullPoints &hullPoints = hull.get();

	// And now that we have the convex hull, simply extract the points enclosing the light point.
	PointIntList::const_iterator lightPosIt = find_if(hullPoints.begin(), hullPoints.end(),
													[] (const PointInt &p) { return p.mUserVal == LightPointTag; } );
	mIsInside = lightPosIt == hullPoints.end();
	if (mIsInside)
		return false;

	PointIntList::const_iterator firstIt	= hullPoints.begin();
	PointIntList::const_iterator lastIt		= hullPoints.end() - 1;

	const Vector2f &v1 = lightPosIt == firstIt	? (*lastIt).mPos	: (*(lightPosIt - 1)).mPos;
	const Vector2f &v2 = lightPosIt == lastIt	? (*firstIt).mPos	: (*(lightPosIt + 1)).mPos;
	const Edge2f occludingEdge(v1, v2);

	Edge2f globalEdge(occluder.getTransform().transformPoint(occludingEdge.v1), occluder.getTransform().transformPoint(occludingEdge.v2));
	generateShadowFromLine(globalEdge);

	return true;
}

void Light::DrawShadows(RenderTarget &target) const
{
	if (mIsInside)
		return;

	for_each(mShadows.begin(), mShadows.end(), [&] (const ShapePtr &shadow) { target.draw(*shadow); } );
}

void Light::DebugDraw(RenderTarget &target) const
{
	if (mIsInside)
		return;

    const sfge::Circle<float> influence(mLightDesc.mPos - sf::Vector2f(mLightDesc.mRadius, mLightDesc.mRadius), mLightDesc.mRadius);
    const sfge::Circle<float> point(mLightDesc.mPos - sf::Vector2f(3, 3), 3);
	target.draw(*shapeFromCircle(influence, Color(150, 150, 30, 64)));
    target.draw(*shapeFromCircle(point, Color::Yellow));
}

void Light::generateShadowFromLine(Edge2f &e)
{
	const Vector2f	scaledPos		= mLightDesc.mPos;
	const float		scaledRadius	= mLightDesc.mRadius;
	const float		sqrScaledRadius	= scaledRadius * scaledRadius;

	// Clamp edge's endpoints to light radius
	Vector2f	lightToV1		= e.v1 - scaledPos,
				lightToV2		= e.v2 - scaledPos;
	const float	lightToV1Dist	= sqrLength(lightToV1),
				lightToV2Dist	= sqrLength(lightToV2);

	if (lightToV1Dist > sqrScaledRadius || lightToV2Dist > sqrScaledRadius)
	{
		EdgeCircleIntersectionCont<float> intersectInfo;
		IntersectionResult res = intersect(e, mLightDesc, intersectInfo);
		if (res != IR_TwoIntersections)
			return;

		if (lightToV1Dist > sqrScaledRadius)
			e.v1 = intersectInfo.mStartPoint + intersectInfo.mTs[0] * intersectInfo.mDir;
		
		if (lightToV2Dist > sqrScaledRadius)
			e.v2 = intersectInfo.mStartPoint + intersectInfo.mTs[1] * intersectInfo.mDir;
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
		const float diffLength	= length(diff);
		const float extrudeLen	= scaledRadius - diffLength + 1.f;

		diff /= diffLength;
		endPoints[i] += diff * extrudeLen;
	}

    // Generate shadow SFML shape
	std::shared_ptr<sf::ConvexShape> shadow(new sf::ConvexShape(2 + endPoints.size()));
    shadow->setFillColor(mShadowFill);
    shadow->setOutlineColor(mShadowOutline);
	shadow->setOutlineThickness(1.f);

    unsigned int ptIndex = 0;
	shadow->setPoint(ptIndex++, e.v1);
	for_each(endPoints.begin(), endPoints.end(),
		[&] (const Vector2f &v)
		{
			sf::Color endShadowFill(mShadowFill);
			endShadowFill.a = static_cast<Uint8>(endShadowFill.a * 0.25f);
			shadow->setPoint(ptIndex++, v);
		} );
	shadow->setPoint(ptIndex++, e.v2);
		
	mShadows.push_back(shadow);
}

}
