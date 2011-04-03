#ifndef SFGE_INFRASTRUCTURE_GAME_HPP
#define SFGE_INFRASTRUCTURE_GAME_HPP

#include <string>
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

		void LoadFile(const std::string &fileName);

	protected:
		virtual void OnDeclareAdditionnalBehaviours()	{ ; }
		virtual void OnEndSystemInit()					{ ; }
		virtual void OnQuit()							{ ; }

	protected:
		typedef std::vector<GameObjectPtr>		GameObjects;

	protected:
		GameObjects		mObjects;
		bool			mQuitFlag;

	private:
		void DeclareBehaviours();
		void Init();
		void LoadWorldFrom(const Parameters &content);
		void LoadGODefinitionFrom(const Parameters &content);
	};
}

#endif
