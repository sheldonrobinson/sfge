template <typename VectorStorageT>
IntersectionResult intersect(const Edge2<VectorStorageT> &e, const Circle<VectorStorageT> &c,
							 EdgeCircleIntersectionCont<VectorStorageT> &out)
{
	out.mStartPoint					= e.v1;
	out.mDir						= e.v2 - out.mStartPoint;
	const float		 edgeDirSqrLen	= sqrLength(out.mDir);
	const Vector2f	 lightToStart	= out.mStartPoint - c.mPos;
	const float		 det			= pow(dot(out.mDir, lightToStart), 2) -
										edgeDirSqrLen * (sqrLength(lightToStart) - c.mRadius * c.mRadius);

	if (det < epsilon<VectorStorageT>())
		return IR_None;

	const float	detRoot				= sqrt(det);
	const float	dDotDelta			= dot(-out.mDir, lightToStart);
	const float invEdgeDirSqrLen	= 1.f / edgeDirSqrLen;

	out.mTs[0] = (dDotDelta - detRoot) * invEdgeDirSqrLen;

	if (realEqual(det, 0.f))
		return IR_Tangent;

	out.mTs[1] = (dDotDelta + detRoot) * invEdgeDirSqrLen;

	return IR_TwoIntersections;
}
