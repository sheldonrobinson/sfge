#ifndef SFGE_INFRASTRUCTURE_TYPE_REGISTRATION_IMPL_HPP
#define SFGE_INFRASTRUCTURE_TYPE_REGISTRATION_IMPL_HPP

#include "sfge/infrastructure/type_registration.hpp"
#include "sfge/infrastructure/infrastructure_fwd.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"

namespace sfge
{
	// POD types
	DEFINE_POD_TYPEID(float);
	DEFINE_POD_TYPEID(int);

	// SFML types
	DEFINE_COMPLEX_TYPEID(sf::Vector2f);
	DEFINE_COMPLEX_TYPEID(sf::Color);

	// SFGE types
	DEFINE_POD_TYPEID(AttributeKey);
	DEFINE_COMPLEX_TYPEID(GameObjectPtr);
	DEFINE_COMPLEX_TYPEID(GameObjectWeakPtr);
	DEFINE_COMPLEX_TYPEID(GraphicSystem::LayerIndex);
}

#endif
