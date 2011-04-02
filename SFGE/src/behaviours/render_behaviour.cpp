#include "sfge/behaviours/render_behaviour.hpp"
#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/builtin_messages.hpp"
#include "sfge/infrastructure/game_object.hpp"

#include <cassert>

namespace sfge
{

RenderBehaviour::RenderBehaviour(GameObjectPtr owner, const Parameters &params, DrawablePtr drawable)
	: Behaviour(owner), mDrawable(drawable)
{
	RegisterAttribute<sf::Color>(AK_Color, &sf::Color::White);

	MessageKey msgKey;
	msgKey.mMessageID	= MID_AttributeChanged;
	msgKey.mSource		= mOwner;
	MessageManager::MessageReceiver slot = MessageManager::MessageReceiver::from_method<RenderBehaviour, &RenderBehaviour::OnAttributeChanged>(this);
	MessageManager::getSingleton().SubscribeTo(msgKey, slot);
}

void RenderBehaviour::OnUpdate(float /*dt*/)
{
	sf::RenderTarget &currTarget = GraphicSystem::getSingleton().GetCurrentRenderTarget();
	currTarget.Draw(*mDrawable);
}

void RenderBehaviour::SetDrawable(DrawablePtr drawable)
{
	mDrawable = drawable;
}

void RenderBehaviour::OnAttributeChanged(const Message &msg)
{
	assert(msg.mSource == mOwner);

	switch (msg.mMsgData)
	{
	case AK_Position:
		{
			const Attribute<sf::Vector2f> pos = GetAttribute<sf::Vector2f>(AK_Position);
			assert(pos.IsValid());
			mDrawable->SetPosition(pos);
		}
		break;
		
	case AK_Color:
		{
			const Attribute<sf::Color> col = GetAttribute<sf::Color>(AK_Color);
			assert(col.IsValid());
			mDrawable->SetColor(col);
		}
		break;
	}
}

}
