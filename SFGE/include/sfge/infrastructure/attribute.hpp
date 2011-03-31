#ifndef SFGE_INFRASTRUCTURE_ATTRIBUTE_HPP
#define SFGE_INFRASTRUCTURE_ATTRIBUTE_HPP

#include <cassert>
#include <memory>

#include "sfge/infrastructure/infrastructure_fwd.hpp"
#include "sfge/infrastructure/detail/attribute_holder.hpp"

namespace sfge
{
	template <typename T>
	class Attribute
	{
	public:
		Attribute(detail::AttributeHolderPtr holder);

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

	private:
		detail::AttributeHolderPtr	mHolder;
	};

#include "attribute.inl"
}

#endif
