#ifndef SFGE_INFRASTRUCTURE_TYPE_REGISTRATION_IMPL_HPP
#define SFGE_INFRASTRUCTURE_TYPE_REGISTRATION_IMPL_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "sfge/infrastructure/type_registration.hpp"

namespace sfge
{
	// POD types
	DEFINE_POD_TYPEID(float);

	// SFML types
	DEFINE_COMPLEX_TYPEID(sf::Vector2f);
	DEFINE_COMPLEX_TYPEID(sf::Color);
}

#endif
