#include "sfge/graphics/graphic_system.hpp"
#include "sfge/infrastructure/game.hpp"
#include "sfge/infrastructure/message_manager.hpp"
#include "sfge/infrastructure/builtin_messages.hpp"

using namespace sf;
using namespace std;

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
		 mRenderWindow.create(params.mHandle, params.mContextSettings);
	 else
		 mRenderWindow.create(params.mMode, params.mWindowTitle, params.mStyle, params.mContextSettings);

	 mRenderWindow.setFramerateLimit(params.mFrameRateLimit);
	 mRenderWindow.setVisible(true);
 }

 bool GraphicSystem::IsMainWindowOpened()
 {
	 return mRenderWindow.isOpen();
 }
 
 sf::RenderWindow& GraphicSystem::GetCurrentRenderWindow()
 {
	 return mRenderWindow;
 }

 RenderTarget& GraphicSystem::GetCurrentRenderTarget()
 {
	 return mRenderWindow;
 }
 
 void GraphicSystem::UpdateEvents()
 {
	Event evt;
	while (mRenderWindow.pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			mRenderWindow.close();
			break;

		case Event::KeyReleased:
            if (evt.key.code == Keyboard::F5)
				mGame->ReloadWorld();
			break;

		case Event::MouseWheelMoved:
			{
				Message msg;
				msg.mID		= MID_MouseWheelTurned;
                msg.mData.SetValue<int>(evt.mouseWheel.delta);

				MessageManager::getSingleton().Queue(msg);
			}
			break;
		};
	}
 }

 void GraphicSystem::PreRender()
 {
	 mRenderWindow.clear();
 }

 void GraphicSystem::PostRender()
 {
	 for_each(mDrawables.begin(), mDrawables.end(),
		 [&] (const LayeredDrawables::value_type &entry)
		 {
			 if (entry.second.mShader)
				GetCurrentRenderTarget().draw(*entry.second.mDrawable, RenderStates(entry.second.mShader.get()));
			 else
				GetCurrentRenderTarget().draw(*entry.second.mDrawable);
		 } );

	 mRenderWindow.display();

	 mDrawables.clear();
 }

 void GraphicSystem::AddDrawableToLayer(LayerIndex layer, DrawablePtr drawable)
 {
	 mDrawables.insert(make_pair(layer, drawable));
 }

}
