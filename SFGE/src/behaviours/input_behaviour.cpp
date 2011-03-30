#include "sfge/behaviours/input_behaviour.hpp"
#include "sfge/graphics/graphic_system.hpp"

namespace sfge
{

InputBehaviour::InputBehaviour(GameObjectPtr owner)
	: Behaviour(owner), mInput(GraphicSystem::getSingleton().GetInput())
{
}

}
