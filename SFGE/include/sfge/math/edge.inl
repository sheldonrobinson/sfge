template <typename VectorStorageT>
typename Edge2<VectorStorageT>::EdgeSide
	Edge2<VectorStorageT>::checkSide(typename const Edge2<VectorStorageT>::vector_type &pt) const
{
	const VectorStorageT s = static_cast<VectorStorageT>((pt.y - v1.y) * (v2.x - v1.x) - (pt.x - v1.x) * (v2.y - v1.y));
	if (s < -epsilon<VectorStorageT>())
		return Edge2::SideRight;

	if (s > epsilon<VectorStorageT>())
		return Edge2::SideLeft;

	return Edge2::SideLie;
}
