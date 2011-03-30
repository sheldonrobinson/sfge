#ifndef SFGE_INFRASTRUCTURE_INFRASTRUCTURE_FWD_HPP
#define SFGE_INFRASTRUCTURE_INFRASTRUCTURE_FWD_HPP

#include <memory>

namespace sfge
{
	class GameObject;
	typedef std::shared_ptr<GameObject>			GameObjectPtr;
	
	class Behaviour;
	typedef std::shared_ptr<Behaviour>			BehaviourPtr;
	
	namespace detail
	{
		class AttributeHolder;
		typedef std::shared_ptr<AttributeHolder>	AttributeHolderPtr;
	}
}

#endif
