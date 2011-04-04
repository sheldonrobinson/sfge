#include "sfge/behaviours/render_sprite_behaviour.hpp"
#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/builtin_messages.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/game.hpp"

#include <cassert>

using namespace boost;
using namespace sf;

namespace sfge
{

RenderSpriteBehaviour::RenderSpriteBehaviour(GameObjectWeakPtr owner)
	: Behaviour(owner)
{
	RegisterAttribute<Color>(AK_Color, &Color::White);
	RegisterAttribute<Vector2f>(AK_Origin);
	RegisterAttribute<GraphicSystem::LayerIndex>(AK_LayerIndex, (GraphicSystem::LayerIndex)0);

	MessageKey msgKey;
	msgKey.mMessageID	= MID_AttributeChanged;
	msgKey.mSource		= mOwner;
	MessageReceiver slot = MessageReceiver::from_method<RenderSpriteBehaviour, &RenderSpriteBehaviour::OnAttributeChanged>(this);
	MessageManager::getSingleton().SubscribeTo(msgKey, slot);
}

void RenderSpriteBehaviour::OnParamsReceived(const Parameters &params)
{
	// TODO move that into some kind of sfml-graphics content factory
	const std::string &src = params.get("source", "");
	assert(!src.empty());
		
	mImage = ImagePtr(new Image());
	mImage->LoadFromFile(mOwner.lock()->GetGame()->GetImagesFolder() + "/" + src);

	mSprite = SpritePtr(new Sprite(*mImage));

	// Apply origin
	optional<float> ox = params.get_optional<float>("ox");
	optional<float> oy = params.get_optional<float>("oy");
	
	Attribute<Vector2f> origin = GetAttribute<Vector2f>(AK_Origin);
	assert(origin.IsValid());
	if (ox)
		origin->x = *ox;
	if (oy)
		origin->y = *oy;

	// Apply layer
	optional<GraphicSystem::LayerIndex> layer = params.get_optional<GraphicSystem::LayerIndex>("layer");
	if (layer)
		GetAttribute<GraphicSystem::LayerIndex>(AK_LayerIndex) = *layer;

	// Apply anything we're interested in due to unknown initialization order
	if (mSprite)
	{
		ApplyTransform();
		ApplyRender();
	}
}

void RenderSpriteBehaviour::OnUpdate(float /*dt*/)
{
	if (!mSprite)
		return;

	const Attribute<GraphicSystem::LayerIndex> layer = GetAttribute<GraphicSystem::LayerIndex>(AK_LayerIndex);
	GraphicSystem::getSingleton().AddDrawableToLayer(layer, mSprite);
}

void RenderSpriteBehaviour::OnAttributeChanged(const Message &msg)
{
	if (!mSprite)
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

void RenderSpriteBehaviour::ApplyTransform()
{
	const Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
	assert(pos.IsValid());
	mSprite->SetPosition(pos);
	
	const Attribute<Vector2f> scale = GetAttribute<Vector2f>(AK_Scale);
	assert(scale.IsValid());
	mSprite->SetScale(scale);
}

void RenderSpriteBehaviour::ApplyRender()
{
	const Attribute<Color> col = GetAttribute<Color>(AK_Color);
	assert(col.IsValid());
	mSprite->SetColor(col);
	
	const Attribute<Vector2f> origin = GetAttribute<Vector2f>(AK_Origin);
	assert(origin.IsValid());
	mSprite->SetOrigin(origin);
}

}
