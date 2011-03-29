inline bool operator<(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
	return	(v1.x < v2.x - epsilon<float>() && v1.y < v2.y - epsilon<float>());
}

inline bool operator==(const sf::Vector2f &v1, const sf::Vector2f &v2)
{
	return	(v1.x > v2.x - epsilon<float>() && v1.x < v2.x + epsilon<float>()) &&
			(v1.y > v2.y - epsilon<float>() && v1.y < v2.y + epsilon<float>());
}

template <typename T>
inline float dot(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
inline float cross(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2, const sf::Vector2<T> &v3)
{
	return (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
}

template <typename T>
inline float sqrLength(const sf::Vector2<T> &v)
{
	return dot(v, v);
}

template <typename T>
inline float length(const sf::Vector2<T> &v)
{
	return sqrt(sqrLength(v));
}

template <typename T>
inline float sqrDistance(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2)
{
	return sqrLength(v1 - v2);
}

template <typename T>
inline void normalize(sf::Vector2<T> &v)
{
	v /= length(v);
}

template <typename T>
inline sf::Vector2f normalize(const sf::Vector2<T> &v)
{
	return Vector2f(v / sqrt(dot(v, v)));
}

template <typename T>
inline float angleBetween(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2)
{
	return atan2(v2.y,v2.x) - atan2(v1.y,v1.x);
}
