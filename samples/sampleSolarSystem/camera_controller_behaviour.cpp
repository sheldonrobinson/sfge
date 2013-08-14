#include "camera_controller_behaviour.hpp"

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/data_store.hpp>
#include <sfge/graphics/graphic_system.hpp>

#include <SFML/Window/Mouse.hpp>

using namespace sfge;
using namespace sf;

CameraControllerBehaviour::CameraControllerBehaviour(GameObjectWeakPtr owner)
	: Behaviour(owner), mStartX(0), mStartY(0), mPrevLButtonState(false)
{
	// We want to check for mouse wheel events (no way to get it via real time input in SFML)
	MessageKey msgKey;
	msgKey.mID	= MID_MouseWheelTurned;
	MessageReceiver slot = MessageReceiver::from_method<CameraControllerBehaviour, &CameraControllerBehaviour::OnMouseWheelTurned>(this);
	MessageManager::getSingleton().SubscribeTo(msgKey, slot);
}

void CameraControllerBehaviour::OnUpdate(float /*dt*/)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
        const Vector2i mousePos = sf::Mouse::getPosition(GraphicSystem::getSingleton().GetCurrentRenderWindow());
        const unsigned int	newX	= mousePos.x,
							newY	= mousePos.y;

		if (!mPrevLButtonState)
		{
			mStartX = newX;
			mStartY = newY;
			mPrevLButtonState = true;
		}
		else if (newX != mStartX || newY != mStartY)
		{
			Vector2f diff((float)mStartX - newX, (float)mStartY - newY);

			Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
	        const Attribute<Vector2f> scale = GetAttribute<Vector2f>(AK_Scale);
	        if (scale.IsValid() && pos.IsValid())
                *pos += (diff * (scale->x / 25.0f));

			mStartX = newX;
			mStartY = newY;
		}
	}
	else
		mPrevLButtonState = false;
}

void CameraControllerBehaviour::OnMouseWheelTurned(const Message &msg)
{
	Attribute<Vector2f> scale = GetAttribute<Vector2f>(AK_Scale);
	assert(scale.IsValid());

	const float ratio = msg.mData.GetValue<int>() * 0.1f;
	*scale = Vector2f(1 - ratio, 1 - ratio);
}
