#ifndef SFGE_INFRASTRUCTURE_BEHAVIOUR_HPP
#define SFGE_INFRASTRUCTURE_BEHAVIOUR_HPP

#include <memory>

#include "sfge/infrastructure/infrastructure_fwd.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/type_registry.hpp"

namespace sfge
{
	class Behaviour
	{
	public:
		virtual ~Behaviour();

		void SetOwner(GameObjectPtr owner);
		
		//! We're just providing a shortcut to GameObject's method
		template <typename T>
		Attribute<T> GetAttribute(size_t attributeKey)		{ return mOwner->GetAttribute<T>(attributeKey); }
		
		//! We're just providing a shortcut to GameObject's method
		template <typename T>
		void RegisterAttribute(size_t attributeKey, const T *defaultVal = nullptr)
		{ return mOwner->RegisterAttribute<T>(attributeKey, defaultVal); }

		template <typename T>
		void RegisterAttribute(size_t attributeKey, const T &defaultVal)
		{ return mOwner->RegisterAttribute<T>(attributeKey, defaultVal); }

		// Methods to reimplement to actually do something useful
		virtual void	OnParamsReceived(const Parameters &params)	{ ; }
		virtual void	OnUpdate(float dt)							{ ; }

	protected:
		Behaviour(GameObjectPtr owner = GameObjectPtr());

	protected:
		GameObjectPtr	mOwner;
	};
}

#endif
