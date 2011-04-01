#include "sfge/behaviours/render_behaviour.hpp"
#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/game_object.hpp"

#include <cassert>

namespace sfge
{

RenderBehaviour::RenderBehaviour(GameObjectPtr owner, DrawablePtr drawable)
	: Behaviour(owner), mDrawable(drawable)
{
	const TypeRegistry::TypeInfo &colorInfo	= TypeRegistry::GetTypeInfoFor("sf::Color");
	RegisterAttribute(AK_RB_COLOR, colorInfo, sf::Color::White);
}

void RenderBehaviour::OnUpdate(float dt)
{
	Attribute<sf::Vector2f> pos = GetAttribute<sf::Vector2f>(AK_GO_POSITION);
	assert(pos.IsValid());
	mDrawable->SetPosition(pos);

	Attribute<sf::Color> col = GetAttribute<sf::Color>(AK_RB_COLOR);
	assert(col.IsValid());
	mDrawable->SetColor(col);

	sf::RenderTarget &currTarget = GraphicSystem::getSingleton().GetCurrentRenderTarget();
	currTarget.Draw(*mDrawable);
}

void RenderBehaviour::SetDrawable(DrawablePtr drawable)
{
	mDrawable = drawable;
}

}
