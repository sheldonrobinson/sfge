#ifndef SFGE_MATH_VECTOR_UTILITIES_HPP
#define SFGE_MATH_VECTOR_UTILITIES_HPP

#include <SFML/System/Vector2.hpp>

#include "sfge/math/numerics.hpp"

namespace sfge
{
	inline bool operator<(const sf::Vector2f &v1, const sf::Vector2f &v2);

	inline bool operator==(const sf::Vector2f &v1, const sf::Vector2f &v2);

	template <typename T>
	inline float dot(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2);

	template <typename T>
	inline float cross(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2, const sf::Vector2<T> &v3);

	template <typename T>
	inline float cross(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2);

	template <typename T>
	inline float sqrLength(const sf::Vector2<T> &v);

	template <typename T>
	inline float length(const sf::Vector2<T> &v);

	template <typename T>
	inline float sqrDistance(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2);

	template <typename T>
	inline void normalize(sf::Vector2<T> &v);

	template <typename T>
	inline sf::Vector2f normalize(const sf::Vector2<T> &v);

	template <typename T>
	inline float angleBetween(const sf::Vector2<T> &v1, const sf::Vector2<T> &v2);

	#include "vector_utilities.inl"
}

#endif
