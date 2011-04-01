#include "sfge/infrastructure/behaviour.hpp"
#include "sfge/infrastructure/game_object.hpp"

namespace sfge
{

Behaviour::Behaviour(GameObjectPtr owner)
	: mOwner(owner)
{
}

Behaviour::~Behaviour()
{
}

}
