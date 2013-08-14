#include "sorlo_input_behaviour.hpp"

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/data_store.hpp>
#include <sfge/graphics/graphic_system.hpp>

#include <SFML/Window/Keyboard.hpp>

using namespace sfge;
using namespace sf;
using namespace std;

SorloInputBehaviour::SorloInputBehaviour(GameObjectWeakPtr owner)
	: Behaviour(owner), mRightKeyPressed(false), mLCtrlKeyPressed(false)
{
}

void SorloInputBehaviour::OnUpdate(float /*dt*/)
{
    const bool rightKeyPressed = sf::Keyboard::isKeyPressed(Keyboard::Right);
	if (rightKeyPressed != mRightKeyPressed)
	{
		if (rightKeyPressed)
			GetAttribute<string>(AK_CurrentAnimName) = "walk";
		else
			GetAttribute<string>(AK_CurrentAnimName) = "idle";

		mRightKeyPressed = rightKeyPressed;
	}

	const bool lctrlKeyPressed = sf::Keyboard::isKeyPressed(Keyboard::LControl);
	if (lctrlKeyPressed != mLCtrlKeyPressed)
	{
		if (lctrlKeyPressed)
			GetAttribute<string>(AK_CurrentAnimName) = "hit_cc";

		mLCtrlKeyPressed = lctrlKeyPressed;
	}
}
