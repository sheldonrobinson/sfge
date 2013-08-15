#ifndef SFGE_SAMPLES_CONTROLLER_LEAP_METALPAD_HPP
#define SFGE_SAMPLES_CONTROLLER_LEAP_METALPAD_HPP

#include <sfge/infrastructure/behaviour.hpp>

class ControllerLeapMetalPad : public sfge::Behaviour
{
public:
	ControllerLeapMetalPad(sfge::GameObjectWeakPtr owner = sfge::GameObjectPtr());

	virtual void OnUpdate(float dt) override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_Impl;
};

#endif
