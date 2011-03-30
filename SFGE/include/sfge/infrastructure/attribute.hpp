#ifndef SFGE_INFRASTRUCTURE_ATTRIBUTE_HPP
#define SFGE_INFRASTRUCTURE_ATTRIBUTE_HPP

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

	private:
		detail::AttributeHolderPtr	mHolder;
	};

#include "attribute.inl"
}

#endif
