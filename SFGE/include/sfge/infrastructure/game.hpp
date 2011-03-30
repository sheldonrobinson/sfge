#ifndef SFGE_INFRASTRUCTURE_GAME_HPP
#define SFGE_INFRASTRUCTURE_GAME_HPP

#include <vector>

#include "sfge/infrastructure/infrastructure_fwd.hpp"

namespace sfge
{
	class Game
	{
	public:
		Game();
		virtual ~Game();

		void Run();
		void Quit()		{ mQuitFlag = true; }

	protected:
		virtual void OnEndSystemInit()		{ ; }
		virtual void OnQuit()				{ ; }

	protected:
		typedef std::vector<GameObjectPtr>		GameObjects;

	protected:
		GameObjects		mObjects;
		bool			mQuitFlag;

	private:
		void Init();
	};
}

#endif
