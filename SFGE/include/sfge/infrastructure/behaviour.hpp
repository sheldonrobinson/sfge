#ifndef SFGE_INFRASTRUCTURE_BEHAVIOUR_HPP
#define SFGE_INFRASTRUCTURE_BEHAVIOUR_HPP

#include <memory>

#include "sfge/infrastructure/infrastructure_fwd.hpp"

namespace sfge
{
	class Behaviour
	{
	public:
		virtual ~Behaviour();
		
		//! We're just providing a shortcut to GameObject's method
		template <typename T>
		Attribute<T>	GetAttribute(size_t attributeKey)		{ return mOwner->GetAttribute<T>(attributeKey); }

		virtual void	OnUpdate(float dt)						{ ; }

	protected:
		Behaviour(GameObjectPtr owner);

	protected:
		GameObjectPtr	mOwner;

	private:
		Behaviour();
	};
}

#endif
