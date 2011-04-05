#ifndef SFGE_SAMPLES_SORLO_INPUT_BEHAVIOUR_HPP
#define SFGE_SAMPLES_SORLO_INPUT_BEHAVIOUR_HPP

#include <sfge/infrastructure/behaviour.hpp>

class SorloInputBehaviour : public sfge::Behaviour
{
public:
	SorloInputBehaviour(sfge::GameObjectWeakPtr owner = sfge::GameObjectPtr());

	virtual void OnUpdate(float dt) override;

private:
	bool mRightKeyPressed;
};

#endif
