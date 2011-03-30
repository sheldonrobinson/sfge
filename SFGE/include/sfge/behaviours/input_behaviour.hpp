#ifndef SFGE_BEHAVIOURS_INPUT_BEHAVIOUR_HPP
#define SFGE_BEHAVIOURS_INPUT_BEHAVIOUR_HPP

#include "sfge/infrastructure/behaviour.hpp"

#include <SFML/Window/Input.hpp>

namespace sfge
{
	class InputBehaviour : public Behaviour
	{
	public:
		InputBehaviour(GameObjectPtr owner);

	protected:
		const sf::Input	&	mInput;
	};
}

#endif
