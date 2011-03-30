#ifndef SFGE_BEHAVIOURS_RENDER_BEHAVIOUR_HPP
#define SFGE_BEHAVIOURS_RENDER_BEHAVIOUR_HPP

#include "sfge/infrastructure/behaviour.hpp"
#include "sfge/graphics/sfml_drawable_ext.hpp"

namespace sfge
{
	class RenderBehaviour : public Behaviour
	{
	public:
		RenderBehaviour(GameObjectPtr owner);

		virtual void OnUpdate(float dt);

	private:
		DrawablePtr		mDrawable;
	};
}

#endif
