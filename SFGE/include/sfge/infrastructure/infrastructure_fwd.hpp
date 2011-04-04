#ifndef SFGE_INFRASTRUCTURE_INFRASTRUCTURE_FWD_HPP
#define SFGE_INFRASTRUCTURE_INFRASTRUCTURE_FWD_HPP

#include <memory>

namespace sfge
{
	class Game;
	typedef Game*								GamePtr;

	class GameObject;
	typedef std::shared_ptr<GameObject>			GameObjectPtr;
	typedef std::weak_ptr<GameObject>			GameObjectWeakPtr;
	
	class Behaviour;
	typedef std::shared_ptr<Behaviour>			BehaviourPtr;

	template <typename T>
	class Attribute;
	
	namespace detail
	{
		class ValueHolder;
		typedef std::shared_ptr<ValueHolder>	ValueHolderPtr;
	}
}

#endif
