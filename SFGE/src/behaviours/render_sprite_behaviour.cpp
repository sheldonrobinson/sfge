#include "sfge/behaviours/render_sprite_behaviour.hpp"

#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/builtin_messages.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/game.hpp"
#include "sfge/infrastructure/message_manager.hpp"
#include "sfge/utilities/ptree_parse_helpers_sfml.hpp"

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
	RegisterAttribute<IntRect>(AK_SpriteRegion, IntRect(-1, -1, -1, -1));

	MessageKey msgKey;
	msgKey.mID		= MID_AttributeChanged;
	msgKey.mSource	= mOwner;
	MessageReceiver slot = MessageReceiver::from_method<RenderSpriteBehaviour, &RenderSpriteBehaviour::OnAttributeChanged>(this);
	MessageManager::getSingleton().SubscribeTo(msgKey, slot);
}

void RenderSpriteBehaviour::OnParamsReceived(const Parameters &params)
{
	// Empty Parameters used as default return value
	const Parameters defParams;

	// Read source filename
	const std::string &src = params.get("source", "");
	assert(!src.empty());
		
	Image img;
	img.loadFromFile(mOwner.lock()->GetGame()->GetImagesFolder() + "/" + src);

	// Apply keycolor
	const Parameters &keyColorParams = params.get_child("keyColor", defParams);
	if (keyColorParams.size() > 0)
	{
		Color keyColor;
		parseTo(keyColorParams, keyColor);
		Uint8 kcoa = params.get("keyColorOutA", 0);

		img.createMaskFromColor(keyColor, kcoa);
	}

    mTexture = TexturePtr(new Texture());
    mTexture->loadFromImage(img);

	mSprite = SpritePtr(new Sprite(*mTexture));
	
	// Apply origin if found
	const Parameters &origin = params.get_child("origin", defParams);
	if (origin.size() > 0)
		parseTo(origin, *GetAttribute<Vector2f>(AK_Origin));

	// Apply smoothing
	optional<bool> smooth = params.get_optional<bool>("smooth");
	if (smooth)
		mTexture->setSmooth(*smooth);

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

void RenderSpriteBehaviour::ApplyTransform()
{
	const Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
	assert(pos.IsValid());
	mSprite->setPosition(pos);
	
	const Attribute<Vector2f> scale = GetAttribute<Vector2f>(AK_Scale);
	assert(scale.IsValid());
	mSprite->setScale(scale);
}

void RenderSpriteBehaviour::ApplyRender()
{
	const Attribute<Color> col = GetAttribute<Color>(AK_Color);
	assert(col.IsValid());
	mSprite->setColor(col);
	
	const Attribute<Vector2f> origin = GetAttribute<Vector2f>(AK_Origin);
	assert(origin.IsValid());
	mSprite->setOrigin(origin);
	
	const Attribute<IntRect> region = GetAttribute<IntRect>(AK_SpriteRegion);
	assert(region.IsValid());
	if (region->top != -1 && region->left != -1 && region->width != -1 && region->height != -1)
		mSprite->setTextureRect(region);
	else
        mSprite->setTextureRect(IntRect(0, 0, mTexture->getSize().x, mTexture->getSize().y));
}

}
