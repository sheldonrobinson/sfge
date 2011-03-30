#ifndef SFGE_BEHAVIOURS_RENDER_BEHAVIOUR_HPP
#define SFGE_BEHAVIOURS_RENDER_BEHAVIOUR_HPP

#include "sfge/infrastructure/behaviour.hpp"

namespace sfge
{
	class RenderBehaviour : public Behaviour
	{
	public:
		virtual void OnUpdate(float dt);
	};
}

#endif
