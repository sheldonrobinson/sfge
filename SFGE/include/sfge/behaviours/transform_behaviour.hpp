#ifndef SFGE_BEHAVIOURS_TRANSFORM_BEHAVIOUR_HPP
#define SFGE_BEHAVIOURS_TRANSFORM_BEHAVIOUR_HPP

#include "sfge/infrastructure/behaviour.hpp"
#include "sfge/infrastructure/message.hpp"

namespace sfge
{
	class TransformBehaviour : public Behaviour
	{
	public:
		TransformBehaviour(GameObjectWeakPtr owner = GameObjectPtr());
	
		virtual void OnParamsReceived(const sfge::Parameters &params) override;
	};
}

#endif
