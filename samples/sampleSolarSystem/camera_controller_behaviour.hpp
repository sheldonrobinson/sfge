#ifndef SFGE_SAMPLES_SOLAR_SYSTEM_CAMERA_CONTROLLER_BEHAVIOUR_HPP
#define SFGE_SAMPLES_SOLAR_SYSTEM_CAMERA_CONTROLLER_BEHAVIOUR_HPP

#include <sfge/infrastructure/behaviour.hpp>

class CameraControllerBehaviour : public sfge::Behaviour
{
public:
	CameraControllerBehaviour(sfge::GameObjectWeakPtr owner = sfge::GameObjectPtr());

	virtual void OnUpdate(float dt) override;

private:
	unsigned int	mPrevMouseX, mPrevMouseY;
	bool			mPrevLButtonState;
};

#endif
