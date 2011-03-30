#include "sfge/infrastructure/game.hpp"
#include "sfge/infrastructure/game_object.hpp"

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

	sf::Clock clock;

	while(!mQuitFlag && GraphicSystem::getSingleton().IsMainWindowOpened())
	{
		GraphicSystem::getSingleton().UpdateEvents();

		for_each(mObjects.begin(), mObjects.end(), [&] (GameObjectPtr go) { go->Update(clock.GetElapsedTime()); } );

		GraphicSystem::getSingleton().Display();
	}

	OnQuit();
}

void Game::Init()
{
	GraphicSystem::Init();

	OnEndSystemInit();
}

}
