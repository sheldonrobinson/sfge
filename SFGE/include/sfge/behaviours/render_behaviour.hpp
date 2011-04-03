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
		RenderBehaviour(GameObjectWeakPtr owner = GameObjectPtr());
		
		virtual void OnParamsReceived(const Parameters &params)	override;
		virtual void OnUpdate(float dt) override;

	private:
		void OnAttributeChanged(const Message &msg);

		void ApplyTransform();
		void ApplyRender();

	private:
		DrawablePtr		mDrawable;
		ImagePtr		mImage;
	};
}

#endif
