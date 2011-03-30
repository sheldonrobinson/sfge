#include "sfge/behaviours/render_behaviour.hpp"
#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/game_object.hpp"

#include <cassert>

#include <SFML/Graphics/Shape.hpp>

namespace sfge
{

RenderBehaviour::RenderBehaviour(GameObjectPtr owner)
	: Behaviour(owner), mDrawable(new sf::Shape(sf::Shape::Circle(0, 0, 50, sf::Color::Magenta)))
{
	mDrawable->SetPosition(400, 300);
}

void RenderBehaviour::OnUpdate(float dt)
{
	Attribute<sf::Vector2f> pos = GetAttribute<sf::Vector2f>(AK_GO_POSITION);
	assert(pos.IsValid());
	mDrawable->SetPosition(pos);

	sf::RenderTarget &currTarget = GraphicSystem::getSingleton().GetCurrentRenderTarget();
	currTarget.Draw(*mDrawable);
}

}
