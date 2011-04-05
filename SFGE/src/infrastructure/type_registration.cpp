#include "sfge/infrastructure/type_registration.hpp"
#include "sfge/infrastructure/type_registration_impl.hpp"

	// POD types
IMPLEMENT_TYPEID_QUERY(float);
IMPLEMENT_TYPEID_QUERY(int);

	// SFML types
IMPLEMENT_TYPEID_QUERY(sf::Vector2f);
IMPLEMENT_TYPEID_QUERY(sf::Color);
IMPLEMENT_TYPEID_QUERY(sf::IntRect);

	// SFGE types
IMPLEMENT_TYPEID_QUERY(sfge::AttributeKey);
IMPLEMENT_TYPEID_QUERY(sfge::GameObjectPtr);
IMPLEMENT_TYPEID_QUERY(sfge::GameObjectWeakPtr);
IMPLEMENT_TYPEID_QUERY(sfge::GraphicSystem::LayerIndex);

void sfge::InitTypesStub()
{
}
