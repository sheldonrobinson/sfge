#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/game.hpp"

using namespace sf;

namespace sfge
{

void GraphicSystem::Init()
 {
	 new GraphicSystem();
 }

 GraphicSystem::~GraphicSystem()
 {
 }

 GraphicSystem::GraphicSystem()
 {
 }

 void GraphicSystem::Create(const InitParams &params)
 {
	 if (params.mHandle)
		 mRenderWindow.Create(params.mHandle, params.mContextSettings);
	 else
		 mRenderWindow.Create(params.mMode, params.mWindowTitle, params.mStyle, params.mContextSettings);

	 mRenderWindow.SetFramerateLimit(params.mFrameRateLimit);
	 mRenderWindow.Show(true);
 }

 bool GraphicSystem::IsMainWindowOpened()
 {
	 return mRenderWindow.IsOpened();
 }

 const Input& GraphicSystem::GetInput()
 {
	 return mRenderWindow.GetInput();
 }
 
 RenderTarget& GraphicSystem::GetCurrentRenderTarget()
 {
	 return mRenderWindow;
 }
 
 void GraphicSystem::UpdateEvents()
 {
	Event evt;
	while (mRenderWindow.GetEvent(evt))
	{
		if (evt.Type == Event::Closed)
			mRenderWindow.Close();

		if (evt.Type == Event::KeyReleased)
		{
			if (evt.Key.Code == Key::F5)
				mGame->ReloadWorld();
		}
	}
 }

 void GraphicSystem::PreRender()
 {
	 mRenderWindow.Clear();
 }

 void GraphicSystem::PostRender()
 {
	 mRenderWindow.Display();
 }

}
