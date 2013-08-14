#include "controller_chng_pos_color_behaviour.hpp"

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/data_store.hpp>
#include <sfge/graphics/graphic_system.hpp>

#include <SFML/Window/Mouse.hpp>

using namespace sfge;
using namespace sf;

ControllerBehaviour::ControllerBehaviour(GameObjectWeakPtr owner)
	: Behaviour(owner)
{
}

void ControllerBehaviour::OnUpdate(float /*dt*/)
{
    // Get mouse coord in our render window
    const sf::Vector2i newPos = sf::Mouse::getPosition(GraphicSystem::getSingleton().GetCurrentRenderWindow());

    if (newPos != mPrevMousePos)
	{
		Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
		assert(pos.IsValid());
        pos->x = static_cast<float>(newPos.x);
		pos->y = static_cast<float>(newPos.y);

        mPrevMousePos = newPos;
	}

	const bool mouseLeftPressed	= sf::Mouse::isButtonPressed(sf::Mouse::Left);
	if (!mPrevLButtonState.is_initialized() || mouseLeftPressed != mPrevLButtonState)
	{
		Attribute<Color> col = GetAttribute<Color>(AK_Color);
		assert(col.IsValid());
		col = mouseLeftPressed ? Color::Blue : Color::Red;

		mPrevLButtonState = mouseLeftPressed;
	}
}
