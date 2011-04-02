#ifndef SFGE_INFRASTRUCTURE_GAME_OBJECT_HPP
#define SFGE_INFRASTRUCTURE_GAME_OBJECT_HPP

#include <cassert>
#include <map>
#include <memory>
#include <vector>

#include "sfge/infrastructure/infrastructure_fwd.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/detail/attribute_holder.hpp"
#include "sfge/infrastructure/type_registry.hpp"
#include "sfge/infrastructure/type_registration.hpp"

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
		template <typename T>
		void			RegisterAttribute(size_t attributeKey, const T *defaultVal = nullptr);
		
		template <typename T>
		Attribute<T>	GetAttribute(size_t attributeKey);

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
	};

#include "game_object.inl"
}

#endif
