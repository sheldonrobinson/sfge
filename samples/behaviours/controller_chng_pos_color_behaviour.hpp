#ifndef SFGE_SAMPLES_CONTROLLER_CHNG_POS_COLOR_BEHAVIOUR_HPP
#define SFGE_SAMPLES_CONTROLLER_CHNG_POS_COLOR_BEHAVIOUR_HPP

#include <sfge/infrastructure/behaviour.hpp>

class ControllerBehaviour : public sfge::Behaviour
{
public:
	ControllerBehaviour(sfge::GameObjectPtr owner = sfge::GameObjectPtr());

	virtual void OnUpdate(float dt) override;

private:
	unsigned int	mPrevMouseX, mPrevMouseY;
	bool			mPrevLButtonState;
};

#endif
