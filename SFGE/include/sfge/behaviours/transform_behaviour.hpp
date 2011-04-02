#ifndef SFGE_BEHAVIOURS_TRANSFORM_BEHAVIOUR_HPP
#define SFGE_BEHAVIOURS_TRANSFORM_BEHAVIOUR_HPP

#include "sfge/infrastructure/behaviour.hpp"
#include "sfge/infrastructure/message_manager.hpp"

namespace sfge
{
	class TransformBehaviour : public Behaviour
	{
	public:
		TransformBehaviour(GameObjectPtr owner, const Parameters &params);
	};
}

#endif
