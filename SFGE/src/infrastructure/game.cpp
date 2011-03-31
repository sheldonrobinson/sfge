#include "sfge/infrastructure/game.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/type_registry.hpp"

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

	OnEndSystemInit();
}

}
