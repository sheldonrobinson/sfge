#ifndef SFGE_INFRASTRUCTURE_GAME_OBJECT_HPP
#define SFGE_INFRASTRUCTURE_GAME_OBJECT_HPP

#include <memory>
#include <map>
#include <vector>

#include "sfge/infrastructure/infrastructure_fwd.hpp"
#include "sfge/infrastructure/type_registry.hpp"

namespace sfge
{
	class GameObject
	{
	public:
		static GameObjectPtr	Create();

		~GameObject();

		// Behaviour management
		void AddBehaviour(BehaviourPtr b);

		// Attribute management
		size_t RegisterAttribute(const TypeRegistry::TypeId typeId);

		// Runtime
		void Update(float dt);

	private:
		GameObject();

	private:
		typedef std::vector<BehaviourPtr>						Behaviours;
		typedef std::map<size_t, detail::AttributeHolderPtr>	Attributes;

	private:
		Behaviours	mBehaviours;

		Attributes	mAttributes;
		size_t		POSITION_ATTRIBUTE;
	};
}

#endif
