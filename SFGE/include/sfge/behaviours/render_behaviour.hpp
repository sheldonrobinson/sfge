#ifndef SFGE_BEHAVIOURS_RENDER_BEHAVIOUR_HPP
#define SFGE_BEHAVIOURS_RENDER_BEHAVIOUR_HPP

#include "sfge/infrastructure/behaviour.hpp"
#include "sfge/infrastructure/message_manager.hpp"
#include "sfge/graphics/sfml_drawable_ext.hpp"

namespace sfge
{
	class RenderBehaviour : public Behaviour
	{
	public:
		RenderBehaviour(GameObjectPtr owner);
		RenderBehaviour(GameObjectPtr owner, DrawablePtr drawable = DrawablePtr());

		virtual void OnUpdate(float dt) override;

		void SetDrawable(DrawablePtr drawable);

	private:
		void OnAttributeChanged(const Message &msg);

	private:
		DrawablePtr		mDrawable;
	};
}

#endif
