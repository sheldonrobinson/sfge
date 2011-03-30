#ifndef SFGE_INFRASTRUCTURE_GAME_OBJECT_HPP
#define SFGE_INFRASTRUCTURE_GAME_OBJECT_HPP

#include <memory>
#include <vector>

namespace sfge
{
	class BehaviourPtr;

	class GameObject;
	typedef std::shared_ptr<GameObject>	GameObjectPtr;

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
