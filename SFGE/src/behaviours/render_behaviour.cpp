#include "sfge/behaviours/render_behaviour.hpp"
#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/builtin_messages.hpp"
#include "sfge/infrastructure/game_object.hpp"

#include <cassert>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>

using namespace sf;

namespace sfge
{

RenderBehaviour::RenderBehaviour(GameObjectPtr owner)
	: Behaviour(owner)
{
	RegisterAttribute<Color>(AK_Color, &Color::White);

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

	// Apply anything we're interested in.
	if (mDrawable)
	{
		ApplyTransform();
		ApplyRender();
	}
}

void RenderBehaviour::OnUpdate(float /*dt*/)
{
	if (!mDrawable)
		return;

	RenderTarget &currTarget = GraphicSystem::getSingleton().GetCurrentRenderTarget();
	currTarget.Draw(*mDrawable);
}

void RenderBehaviour::OnAttributeChanged(const Message &msg)
{
	if (!mDrawable)
		return;

	assert(msg.mSource == mOwner);

	switch (msg.mMsgData)
	{
	case AK_Position:
		ApplyTransform();
		break;
		
	case AK_Color:
		ApplyRender();
		break;
	}
}

void RenderBehaviour::ApplyTransform()
{
	const Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
	assert(pos.IsValid());
	mDrawable->SetPosition(pos);
}

void RenderBehaviour::ApplyRender()
{
	const Attribute<Color> col = GetAttribute<Color>(AK_Color);
	assert(col.IsValid());
	mDrawable->SetColor(col);
}

}
