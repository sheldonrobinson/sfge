#ifndef SFGE_INFRASTRUCTURE_GAME_HPP
#define SFGE_INFRASTRUCTURE_GAME_HPP

#include "sfge/infrastructure/infrastructure_fwd.hpp"
#include "sfge/infrastructure/data_store.hpp"

#include <string>
#include <vector>

#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>

namespace sfge
{
	class Game
	{
	public:
		Game();
		virtual ~Game();
		
		void Init();
		void ProcessOneFrame();
		void Run();
		void Quit()		{ mQuitFlag = true; }

		const std::string& GetWorldDefsFolder() const	{ return mWorldDefsFolder; }
		const std::string& GetGODefsFolder() const		{ return mGODefsFolder; }
		const std::string& GetImagesFolder() const		{ return mImagesFolder; }
		const std::string& GetCurrentWorldName() const	{ return mCurrentWorld; }

		void LoadWorld(const std::string &worldName);
		void LoadGameObjectDef(const std::string &godName);
		void ReloadWorld();
		void ClearWorld();

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
		std::string		mImagesFolder;

		std::string		mCurrentWorld;

		sf::Clock		mClock;

	private:
		void DeclareBehaviours();
		void LoadConfigFile();
		void LoadWorldFrom(const Parameters &content);
		void LoadGODefinitionFrom(const Parameters &content);
		DataStore::BehaviourParameters ParseInstanceParams(const std::string &godName, const std::string &instanceName, const Parameters &content);
	};
}

#endif
