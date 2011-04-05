#include "sorlo_input_behaviour.hpp"

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/data_store.hpp>
#include <sfge/graphics/graphic_system.hpp>

using namespace sfge;
using namespace sf;
using namespace std;

SorloInputBehaviour::SorloInputBehaviour(GameObjectWeakPtr owner)
	: Behaviour(owner), mRightKeyPressed(false)
{
}

void SorloInputBehaviour::OnUpdate(float /*dt*/)
{
	const sf::Input	&input(GraphicSystem::getSingleton().GetInput());

	const bool	rightKeyPressed	= input.IsKeyDown(Key::Right);

	if (rightKeyPressed != mRightKeyPressed)
	{
		if (rightKeyPressed)
			GetAttribute<string>(AK_CurrentAnimName) = "walk";
		else
			GetAttribute<string>(AK_CurrentAnimName) = "idle";

		mRightKeyPressed = rightKeyPressed;
	}
}
