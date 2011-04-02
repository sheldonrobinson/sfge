#ifndef SFGE_INFRASTRUCTURE_INFRASTRUCTURE_FWD_HPP
#define SFGE_INFRASTRUCTURE_INFRASTRUCTURE_FWD_HPP

#include <memory>
#include <utility>
#include <vector>

namespace sfge
{
	class GameObject;
	typedef std::shared_ptr<GameObject>			GameObjectPtr;
	
	class Behaviour;
	typedef std::shared_ptr<Behaviour>			BehaviourPtr;

	template <typename T>
	class Attribute;

	typedef std::pair<std::string, std::string>		Parameter;
	typedef std::vector<Parameter>					Parameters;
	
	namespace detail
	{
		class AttributeHolder;
		typedef std::shared_ptr<AttributeHolder>	AttributeHolderPtr;
	}
}

#endif
