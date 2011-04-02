#include "sfge/infrastructure/game.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/type_registry.hpp"
#include "sfge/infrastructure/message_manager.hpp"
#include "sfge/infrastructure/data_store.hpp"

#include "sfge/behaviours/render_behaviour.hpp"
#include "sfge/behaviours/transform_behaviour.hpp"

#include "sfge/graphics/graphic_system.hpp"

#include <algorithm>
#include <SFML/System/Clock.hpp>

using namespace std;

namespace sfge
{

Game::Game()
	: mQuitFlag(false)
{
}

Game::~Game()
{
}

void Game::Run()
{
	Init();
	
	GraphicSystem &gfxSys = GraphicSystem::getSingleton();

	sf::Clock clock;

	while(!mQuitFlag && GraphicSystem::getSingleton().IsMainWindowOpened())
	{
		gfxSys.UpdateEvents();
		gfxSys.PreRender();

		for_each(mObjects.begin(), mObjects.end(), [&] (GameObjectPtr go) { go->Update(clock.GetElapsedTime()); } );

		gfxSys.PostRender();
	}

	OnQuit();
}

void Game::Init()
{
	sfge::InitTypesStub();

	GraphicSystem::Init();
	MessageManager::Init();
	DataStore::Init();
	DeclareBehaviours();

	OnEndSystemInit();
}

void Game::DeclareBehaviours()
{
	// Declare built-in behaviours
	DECLARE_BEHAVIOUR(TransformBehaviour);
	DECLARE_BEHAVIOUR(RenderBehaviour);

	// Allow user to declare any additionnal behaviour
	OnDeclareAdditionnalBehaviours();
}

}
