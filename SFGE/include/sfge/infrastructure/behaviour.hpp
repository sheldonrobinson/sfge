#ifndef SFGE_INFRASTRUCTURE_BEHAVIOUR_HPP
#define SFGE_INFRASTRUCTURE_BEHAVIOUR_HPP

#include <memory>

#include "sfge/infrastructure/infrastructure_fwd.hpp"

namespace sfge
{
	class Behaviour
	{
	public:
		virtual ~Behaviour();

		virtual void OnUpdate(float dt)		{ ; }

	protected:
		Behaviour(GameObjectPtr owner);

	protected:
		GameObjectPtr	mOwner;

	private:
		Behaviour();
	};
}

#endif
