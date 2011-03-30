#include "sfge/behaviours/render_behaviour.hpp"
#include "sfge/graphics/graphic_system.hpp"

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
	sf::RenderTarget &currTarget = GraphicSystem::getSingleton().GetCurrentRenderTarget();

	currTarget.Draw(*mDrawable);
}

}
