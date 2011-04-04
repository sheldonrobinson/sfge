#include "sfge/infrastructure/type_registration.hpp"
#include "sfge/infrastructure/type_registration_impl.hpp"

	// POD types
IMPLEMENT_TYPEID_QUERY(float);

	// SFML types
IMPLEMENT_TYPEID_QUERY(sf::Vector2f);
IMPLEMENT_TYPEID_QUERY(sf::Color);

	// SFGE types
IMPLEMENT_TYPEID_QUERY(sfge::GameObjectPtr);
IMPLEMENT_TYPEID_QUERY(sfge::GameObjectWeakPtr);
IMPLEMENT_TYPEID_QUERY(sfge::GraphicSystem::LayerIndex);

void sfge::InitTypesStub()
{
}
