#include "controller_chng_pos_color_behaviour.hpp"

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/data_store.hpp>
#include <sfge/graphics/graphic_system.hpp>

using namespace sfge;
using namespace sf;

ControllerBehaviour::ControllerBehaviour(GameObjectPtr owner)
	: Behaviour(owner), mPrevMouseX(0), mPrevMouseY(0), mPrevLButtonState(false)
{
}

void ControllerBehaviour::OnUpdate(float /*dt*/)
{
	const sf::Input	&input(GraphicSystem::getSingleton().GetInput());

	const unsigned int	newX	= input.GetMouseX(),
						newY	= input.GetMouseY();

	if (newX != mPrevMouseX || newY != mPrevMouseY)
	{
		Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
		assert(pos.IsValid());
		pos->x = static_cast<float>(newX);
		pos->y = static_cast<float>(newY);

		mPrevMouseX = newX;
		mPrevMouseY = newY;
	}

	const bool mouseLeftPressed	= input.IsMouseButtonDown(sf::Mouse::Left);
	if (mouseLeftPressed != mPrevLButtonState)
	{
		Attribute<Color> col = GetAttribute<Color>(AK_Color);
		assert(col.IsValid());
		col = mouseLeftPressed ? Color::Blue : Color::Red;

		mPrevLButtonState = mouseLeftPressed;
	}
}
