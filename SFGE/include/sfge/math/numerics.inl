template <typename T>
inline T epsilon()
{
	return std::numeric_limits<T>::epsilon();
}

template <typename RealT>
inline bool realEqual(RealT x, RealT y)
{
	return x > (y - epsilon<RealT>()) && x < (y + epsilon<RealT>());
}
