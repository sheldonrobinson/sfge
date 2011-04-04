#include "camera_controller_behaviour.hpp"

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/data_store.hpp>
#include <sfge/graphics/graphic_system.hpp>

#include <iostream>

using namespace std;
using namespace sfge;
using namespace sf;

CameraControllerBehaviour::CameraControllerBehaviour(GameObjectWeakPtr owner)
	: Behaviour(owner), mPrevMouseX(0), mPrevMouseY(0), mPrevLButtonState(false)
{
}

void CameraControllerBehaviour::OnUpdate(float /*dt*/)
{
	GraphicSystem &gfxSys = GraphicSystem::getSingleton();
	const sf::Input	&input(gfxSys.GetInput());

	if (input.IsMouseButtonDown(sf::Mouse::Left))
	{
		const unsigned int	newX	= input.GetMouseX(),
							newY	= input.GetMouseY();

		if (!mPrevLButtonState)
		{
			mPrevMouseX = newX;
			mPrevMouseY = newY;
			mPrevLButtonState = true;
			
			Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
			assert(pos.IsValid());
			pos = gfxSys.GetCurrentRenderTarget().ConvertCoords(mPrevMouseX, mPrevMouseY);

			return;
		}

		if (newX != mPrevMouseX || newY != mPrevMouseY)
		{
			Vector2f diff((float)mPrevMouseX - newX, (float)mPrevMouseY - newY);
			cout << "Translate by <" << diff.x << "; " << diff.y << ">" << endl;

			Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
			assert(pos.IsValid());
			*pos += diff;

			mPrevMouseX = newX;
			mPrevMouseY = newY;
		}

	}
	else
		mPrevLButtonState = false;
}
