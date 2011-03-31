#include "sfge/infrastructure/type_registration.hpp"
#include "sfge/infrastructure/type_registration_impl.hpp"

#include <SFML/System/Vector2.hpp>

IMPLEMENT_TYPEID_QUERY(float);
IMPLEMENT_TYPEID_QUERY(sf::Vector2f);

void sfge::InitTypesStub()
{
}
