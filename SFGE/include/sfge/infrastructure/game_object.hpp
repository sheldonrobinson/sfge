#ifndef SFGE_INFRASTRUCTURE_GAME_OBJECT_HPP
#define SFGE_INFRASTRUCTURE_GAME_OBJECT_HPP

#include <memory>
#include <vector>

#include "sfge/infrastructure/infrastructure_fwd.hpp"

namespace sfge
{
	class GameObject
	{
	public:
		static GameObjectPtr Create();

		~GameObject();

		void Update(float dt);

	private:
		GameObject();

	private:
		typedef std::vector<BehaviourPtr>	Behaviours;

	private:
		Behaviours	mBehaviours;
	};
}

#endif
