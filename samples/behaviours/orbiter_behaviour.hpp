#ifndef SFGE_SAMPLES_ORBITER_BEHAVIOUR_HPP
#define SFGE_SAMPLES_ORBITER_BEHAVIOUR_HPP

#include <sfge/infrastructure/behaviour.hpp>

class OrbiterBehaviour : public sfge::Behaviour
{
public:
	OrbiterBehaviour(sfge::GameObjectWeakPtr owner = sfge::GameObjectPtr());
	
	virtual void OnParamsReceived(const sfge::Parameters &params) override;

	virtual void OnUpdate(float dt) override;

private:
	float	mAccum;
};

#endif
