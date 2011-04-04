#ifndef SFGE_BEHAVIOURS_CAMERA_BEHAVIOUR_HPP
#define SFGE_BEHAVIOURS_CAMERA_BEHAVIOUR_HPP

#include "sfge/infrastructure/behaviour.hpp"
#include "sfge/infrastructure/message_manager.hpp"

namespace sfge
{
	class CameraBehaviour : public Behaviour
	{
	public:
		CameraBehaviour(GameObjectWeakPtr owner = GameObjectPtr());
	
		virtual void OnParamsReceived(const sfge::Parameters &params) override;

	private:
		void OnAttributeChanged(const Message &msg);
	};
}

#endif
