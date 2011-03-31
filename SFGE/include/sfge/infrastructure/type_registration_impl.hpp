#ifndef SFGE_INFRASTRUCTURE_TYPE_REGISTRATION_IMPL_HPP
#define SFGE_INFRASTRUCTURE_TYPE_REGISTRATION_IMPL_HPP

#include <SFML/System/Vector2.hpp>

#include "sfge/infrastructure/type_registration.hpp"

namespace sfge
{
	// POD types
	DEFINE_TYPEID_QUERY(float);

	// SFML types
	DEFINE_TYPEID_QUERY(sf::Vector2f);
}

#endif
