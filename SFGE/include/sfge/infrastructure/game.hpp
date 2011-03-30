#ifndef SFGE_INFRASTRUCTURE_GAME_HPP
#define SFGE_INFRASTRUCTURE_GAME_HPP

#include <vector>

namespace sfge
{
	class GameObjectPtr;

	class Game
	{
	public:
		Game();
		virtual ~Game();

	protected:
		typedef std::vector<GameObjectPtr>		GameObjects;

	protected:
		GameObjects		mObjects;
	};
}

#endif
