#ifndef SFGE_INFRASTRUCTURE_GAME_OBJECT_HPP
#define SFGE_INFRASTRUCTURE_GAME_OBJECT_HPP

#include <cassert>
#include <map>
#include <memory>
#include <vector>

#include "sfge/infrastructure/infrastructure_fwd.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/detail/value_holder.hpp"
#include "sfge/infrastructure/type_registry.hpp"
#include "sfge/infrastructure/type_registration.hpp"

namespace sfge
{
	class GameObject
	{
	public:
		GameObject();
		void SetSelf(GameObjectWeakPtr selfPtr)	{ mSelf = selfPtr; }

		~GameObject();

		// Game relationship
		void	SetGame(GamePtr g)		{ mGame = g; }
		GamePtr	GetGame() const			{ return mGame; }

		// Behaviour management
		void AddBehaviour(BehaviourPtr b);

		// Attribute management
		template <typename T>
		void			RegisterAttribute(size_t attributeKey, const T *defaultVal = nullptr);
		template <typename T>
		void			RegisterAttribute(size_t attributeKey, const T &defaultVal);
		
		template <typename T>
		Attribute<T>	GetAttribute(size_t attributeKey);

		// Runtime
		void Update(float dt);

	private:

	private:
		typedef std::vector<BehaviourPtr>					Behaviours;
		typedef std::map<size_t, detail::ValueHolderPtr>	Attributes;

	private:
		GameObjectWeakPtr	mSelf;			//!< Used when sending messages

		GamePtr			mGame;

		Behaviours		mBehaviours;
		// FIXME THREADING move that somewhere else for potentially nicer parallelism performances. Datastore too I guess?
		Attributes		mAttributes;
	};

#include "game_object.inl"
}

#endif
