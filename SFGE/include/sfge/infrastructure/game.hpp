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

		void LoadWorld(const std::string &worldName);
		void LoadGameObjectDef(const std::string &godName);

	protected:
		virtual void OnDeclareAdditionnalBehaviours()	{ ; }
		virtual void OnEndSystemInit()					{ ; }
		virtual void OnQuit()							{ ; }

	protected:
		typedef std::vector<GameObjectPtr>		GameObjects;

	protected:
		GameObjects		mObjects;
		bool			mQuitFlag;
		std::string		mConfigFileName;
		
		std::string		mWorldDefsFolder;
		std::string		mGODefsFolder;

	private:
		void DeclareBehaviours();
		void Init();
		void LoadConfigFile();
		void LoadWorldFrom(const Parameters &content);
		void LoadGODefinitionFrom(const Parameters &content);
	};
}

#endif
