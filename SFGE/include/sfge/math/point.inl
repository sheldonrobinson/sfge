template <typename VectorStorageT, typename UserValT>
inline bool operator<(const Point<VectorStorageT, UserValT> &p1,
					  const Point<VectorStorageT, UserValT> &p2)
{
	return p1.mUserVal < p2.mUserVal;
}

template <typename VectorStorageT>
inline bool operator<(const Point<VectorStorageT, void> &p1,
					  const Point<VectorStorageT, void> &p2)
{
	return p1.mPos < p2.mPos;
}
	
template <typename VectorStorageT, typename UserValT>
bool operator==(const Point<VectorStorageT, UserValT> &p1,
				const Point<VectorStorageT, UserValT> &p2)
{
	return	(p1.mUserVal > p2.mUserVal - epsilon<VectorStorageT>()) &&
			(p1.mUserVal < p2.mUserVal + epsilon<VectorStorageT>()) &&
			(p1.mPos == p2.mPos);
}
	
template <typename VectorStorageT>
bool operator==(const Point<VectorStorageT, void> &p1,
				const Point<VectorStorageT, void> &p2)
{
	return	p1.mPos == p2.mPos;
}
