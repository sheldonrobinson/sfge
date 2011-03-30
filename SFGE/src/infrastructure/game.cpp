#include "sfge/infrastructure/game.hpp"
#include "sfge/infrastructure/game_object.hpp"

#include "sfge/graphics/graphic_system.hpp"

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

	while(!mQuitFlag && GraphicSystem::getSingleton().IsMainWindowOpened())
	{
		GraphicSystem::getSingleton().UpdateEvents();
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
