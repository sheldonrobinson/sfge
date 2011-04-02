#include "sfge/behaviours/render_behaviour.hpp"
#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/builtin_messages.hpp"
#include "sfge/infrastructure/game_object.hpp"

#include <cassert>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>

using namespace std;
using namespace sf;

namespace sfge
{

RenderBehaviour::RenderBehaviour(GameObjectPtr owner)
	: Behaviour(owner)
{
	RegisterAttribute<sf::Color>(AK_Color, &sf::Color::White);

	MessageKey msgKey;
	msgKey.mMessageID	= MID_AttributeChanged;
	msgKey.mSource		= mOwner;
	MessageReceiver slot = MessageReceiver::from_method<RenderBehaviour, &RenderBehaviour::OnAttributeChanged>(this);
	MessageManager::getSingleton().SubscribeTo(msgKey, slot);
}

void RenderBehaviour::OnParamsReceived(const Parameters &params)
{
	// TODO move that into some kind of sfml-graphics content factory
	if (params.get("type", "") == "shape")
	{
		if (params.get("shape", "") == "circle")
		{
			float cx		= params.get("cx",		0.f);
			float cy		= params.get("cy",		0.f);
			float radius	= params.get("radius",	0.f);

			Color color;
			color.r	= params.get("cr",	0);
			color.g	= params.get("cg",	0);
			color.b	= params.get("cb",	0);
			color.a	= params.get("ca",	0);

			mDrawable = DrawablePtr(new Shape(Shape::Circle(cx, cy, radius, color)));
		}
	}
}

void RenderBehaviour::OnUpdate(float /*dt*/)
{
	if (!mDrawable)
		return;

	sf::RenderTarget &currTarget = GraphicSystem::getSingleton().GetCurrentRenderTarget();
	currTarget.Draw(*mDrawable);
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
