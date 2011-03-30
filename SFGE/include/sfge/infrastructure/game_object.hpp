#ifndef SFGE_INFRASTRUCTURE_GAME_OBJECT_HPP
#define SFGE_INFRASTRUCTURE_GAME_OBJECT_HPP

#include <memory>

namespace sfge
{
	class GameObject;
	typedef std::shared_ptr<GameObject>	GameObjectPtr;

	class GameObject
	{
	public:
		static GameObjectPtr Create();

		~GameObject();

		void OnUpdate(float dt);

	private:
		GameObject();
	};
}

#endif
