#include "sfge/behaviours/render_shape_behaviour.hpp"

#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/builtin_messages.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/message_manager.hpp"
#include "sfge/infrastructure/game.hpp"
#include "sfge/utilities/ptree_parse_helpers_sfml.hpp"
#include "sfge/graphics/sfml_shape_ext.hpp"

#include <cassert>

using namespace boost;
using namespace sf;

namespace sfge
{

RenderShapeBehaviour::RenderShapeBehaviour(GameObjectWeakPtr owner)
	: Behaviour(owner)
{
	RegisterAttribute<Color>(AK_Color, &Color::White);
	RegisterAttribute<Vector2f>(AK_Origin);

	MessageKey msgKey;
	msgKey.mID		= MID_AttributeChanged;
	msgKey.mSource	= mOwner;
	MessageReceiver slot = MessageReceiver::from_method<RenderShapeBehaviour, &RenderShapeBehaviour::OnAttributeChanged>(this);
	MessageManager::getSingleton().SubscribeTo(msgKey, slot);
}

void RenderShapeBehaviour::OnParamsReceived(const Parameters &params)
{
	// Empty Parameters used as default return value
	const Parameters defParams;

    Vector2f defaultOrigin;
	if (params.get("shape", "") == "circle")
	{
		Vector2f center;
		const Parameters &centerParams = params.get_child("center", defParams);
		if (!centerParams.empty())
			parseTo(centerParams, center);

		float radius = params.get("radius",	0.f);

		Color color(Color::Magenta);
		const Parameters &colorParams = params.get_child("color", defParams);
		if (!colorParams.empty())
			parseTo(colorParams, color);

		mShape = shapeFromCircle(sfge::Circle<float>(center, radius), color);
        // Since SFML 2 (release version), circle's position indicate top left; until proven that majority loves it, defaults back to mid shape.
        defaultOrigin = Vector2f(radius, radius);
	}
	
	// Apply origin if found
	const Parameters &origin = params.get_child("origin", defParams);
	if (origin.size() > 0)
		parseTo(origin, *GetAttribute<Vector2f>(AK_Origin));
    else
        *GetAttribute<Vector2f>(AK_Origin) = defaultOrigin;

	// Apply anything we're interested in due to unknown initialization order
	if (mShape)
	{
		ApplyTransform();
		ApplyRender();
	}
}

void RenderShapeBehaviour::OnUpdate(float /*dt*/)
{
	if (!mShape)
		return;

	const Attribute<GraphicSystem::LayerIndex> layer = GetAttribute<GraphicSystem::LayerIndex>(AK_LayerIndex);
	GraphicSystem::getSingleton().AddDrawableToLayer(layer, mShape);
}

void RenderShapeBehaviour::OnAttributeChanged(const Message &msg)
{
	if (!mShape)
		return;

	assert(msg.mSource.lock().get() == mOwner.lock().get());

	switch (msg.mData.GetValue<AttributeKey>())
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

void RenderShapeBehaviour::ApplyTransform()
{
	const Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
	assert(pos.IsValid());
	mShape->setPosition(pos);
	
	const Attribute<Vector2f> scale = GetAttribute<Vector2f>(AK_Scale);
	assert(scale.IsValid());
	mShape->setScale(scale);
}

void RenderShapeBehaviour::ApplyRender()
{
	const Attribute<Color> col = GetAttribute<Color>(AK_Color);
	assert(col.IsValid());
	mShape->setFillColor(col);
	
	const Attribute<Vector2f> origin = GetAttribute<Vector2f>(AK_Origin);
	assert(origin.IsValid());
	mShape->setOrigin(origin);
}

}
