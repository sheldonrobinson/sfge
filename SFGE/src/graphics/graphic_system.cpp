#include "sfge/graphics/graphic_system.hpp"

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

 const sf::Input& GraphicSystem::GetInput()
 {
	 return mRenderWindow.GetInput();
 }
 
 sf::RenderTarget& GraphicSystem::GetCurrentRenderTarget()
 {
	 return mRenderWindow;
 }
 
 void GraphicSystem::UpdateEvents()
 {
	sf::Event evt;
	while (mRenderWindow.GetEvent(evt))
	{
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
