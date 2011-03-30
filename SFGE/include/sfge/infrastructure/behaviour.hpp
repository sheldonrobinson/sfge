#ifndef SFGE_INFRASTRUCTURE_BEHAVIOUR_HPP
#define SFGE_INFRASTRUCTURE_BEHAVIOUR_HPP

#include <memory>

namespace sfge
{
	class Behaviour;
	typedef std::shared_ptr<Behaviour>	BehaviourPtr;

	class Behaviour
	{
	public:
		virtual ~Behaviour();

		virtual void OnUpdate(float dt)		{ ; }

	protected:
		Behaviour();
	};
}

#endif
