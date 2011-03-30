#include "sfge/behaviours/render_behaviour.hpp"
#include "sfge/graphics/graphic_system.hpp"

#include <SFML/Graphics/Shape.hpp>

namespace sfge
{

void RenderBehaviour::OnUpdate(float dt)
{
	sf::RenderTarget &currTarget = GraphicSystem::getSingleton().GetCurrentRenderTarget();

	sf::Shape s(sf::Shape::Circle(400, 300, 50, sf::Color::Magenta));
	currTarget.Draw(s);
}

}
