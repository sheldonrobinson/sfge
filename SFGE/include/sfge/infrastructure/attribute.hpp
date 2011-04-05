#ifndef SFGE_INFRASTRUCTURE_ATTRIBUTE_HPP
#define SFGE_INFRASTRUCTURE_ATTRIBUTE_HPP

#include <cassert>
#include <memory>

#include "sfge/infrastructure/infrastructure_fwd.hpp"
#include "sfge/infrastructure/detail/value_holder.hpp"
#include "sfge/infrastructure/message_manager.hpp"
#include "sfge/infrastructure/builtin_messages.hpp"

namespace sfge
{
	template <typename T>
	class Attribute
	{
	public:
		Attribute(detail::ValueHolderPtr holder, GameObjectWeakPtr owner, size_t attrKey);
		~Attribute();

		bool IsValid() const;
		
		const T& Get() const;
		T& Get();

		// Indirection operators
		T& operator*();
		const T& operator*() const;
		T* operator->();
		const T* const operator->() const;

		// Assignement operators
		void operator=(const T &v);

		// Cast operators
		operator T() const;
		operator bool() const;

	private:
		detail::ValueHolderPtr	mHolder;
		GameObjectWeakPtr		mOwner;
		size_t					mAttributeKey;
		
		//! Set to true whenever any non-const accessor is used. No way to really check modifications without caching I guess.
		mutable bool			mPotentiallyModified;
	};

#include "attribute.inl"
}

#endif
