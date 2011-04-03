#include "sfge/infrastructure/type_registration.hpp"
#include "sfge/infrastructure/type_registration_impl.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

	// POD types
IMPLEMENT_TYPEID_QUERY(float);

	// SFML types
IMPLEMENT_TYPEID_QUERY(sf::Vector2f);
IMPLEMENT_TYPEID_QUERY(sf::Color);

	// SFGE types
IMPLEMENT_TYPEID_QUERY(sfge::GameObjectPtr);
IMPLEMENT_TYPEID_QUERY(sfge::GameObjectWeakPtr);

void sfge::InitTypesStub()
{
}
