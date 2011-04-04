#ifndef SFGE_SAMPLES_SOLAR_SYSTEM_CAMERA_CONTROLLER_BEHAVIOUR_HPP
#define SFGE_SAMPLES_SOLAR_SYSTEM_CAMERA_CONTROLLER_BEHAVIOUR_HPP

#include <sfge/infrastructure/behaviour.hpp>
#include <sfge/infrastructure/message_manager.hpp>

class CameraControllerBehaviour : public sfge::Behaviour
{
public:
	CameraControllerBehaviour(sfge::GameObjectWeakPtr owner = sfge::GameObjectPtr());

	virtual void OnUpdate(float dt) override;

private:
	void OnMouseWheelTurned(const sfge::Message &msg);

private:
	unsigned int	mStartX, mStartY;
	bool			mPrevLButtonState;
};

#endif
