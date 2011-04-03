#include "sfge/behaviours/render_behaviour.hpp"
#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/builtin_messages.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/game.hpp"

#include <cassert>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>

using namespace boost;
using namespace sf;

namespace sfge
{

RenderBehaviour::RenderBehaviour(GameObjectWeakPtr owner)
	: Behaviour(owner)
{
	RegisterAttribute<Color>(AK_Color, &Color::White);
	RegisterAttribute<Vector2f>(AK_Origin);

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
	else if (params.get("type", "") == "sprite")
	{
		const std::string &src = params.get("source", "");
		assert(!src.empty());
		
		mImage = ImagePtr(new Image());
		mImage->LoadFromFile(mOwner.lock()->GetGame()->GetImagesFolder() + "/" + src);

		mDrawable = DrawablePtr(new Sprite(*mImage));
	}

	// Apply origin
	optional<float> ox = params.get_optional<float>("ox");
	optional<float> oy = params.get_optional<float>("oy");
	
	Attribute<Vector2f> origin = GetAttribute<Vector2f>(AK_Origin);
	assert(origin.IsValid());
	if (ox)
		origin->x = *ox;
	if (oy)
		origin->y = *oy;

	// Apply anything we're interested in due to unknown initialization order
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

	assert(msg.mSource.lock().get() == mOwner.lock().get());

	switch (msg.mMsgData)
	{
	case AK_Position:
	case AK_Scale:
		ApplyTransform();
		break;
		
	case AK_Color:
	case AK_Origin:
		ApplyRender();
		break;
	}
}

void RenderBehaviour::ApplyTransform()
{
	const Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
	assert(pos.IsValid());
	mDrawable->SetPosition(pos);
	
	const Attribute<Vector2f> scale = GetAttribute<Vector2f>(AK_Scale);
	assert(scale.IsValid());
	mDrawable->SetScale(scale);
}

void RenderBehaviour::ApplyRender()
{
	const Attribute<Color> col = GetAttribute<Color>(AK_Color);
	assert(col.IsValid());
	mDrawable->SetColor(col);
	
	const Attribute<Vector2f> origin = GetAttribute<Vector2f>(AK_Origin);
	assert(origin.IsValid());
	mDrawable->SetOrigin(origin);
}

}
