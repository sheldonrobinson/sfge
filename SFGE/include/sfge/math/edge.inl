template <typename VectorStorageT>
typename Edge2<VectorStorageT>::EdgeSide
	Edge2<VectorStorageT>::checkSide(typename const Edge2<VectorStorageT>::vector_type &pt) const
{
	const VectorStorageT s = cross(v1, v2, pt);
	if (s < -epsilon<VectorStorageT>())
		return Edge2::SideRight;

	if (s > epsilon<VectorStorageT>())
		return Edge2::SideLeft;

	return Edge2::SideLie;
}
