#include "sfge/behaviours/transform_behaviour.hpp"
#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/builtin_messages.hpp"
#include "sfge/infrastructure/game_object.hpp"

#include <cassert>

namespace sfge
{

TransformBehaviour::TransformBehaviour(GameObjectPtr owner)
	: Behaviour(owner)
{
	RegisterAttribute<sf::Vector2f>(AK_Position);
}

}
