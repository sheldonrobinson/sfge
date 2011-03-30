#ifndef SFGE_INFRASTRUCTURE_ATTRIBUTE_HOLDER_HPP
#define SFGE_INFRASTRUCTURE_ATTRIBUTE_HOLDER_HPP

#include <SFML/Config.hpp>

#include <memory>

#include "sfge/infrastructure/type_registry.hpp"

namespace sfge
{
	namespace detail
	{
		class AttributeHolder
		{
		public:
			typedef void*	ValueT;

		public:
			AttributeHolder(TypeRegistry::TypeId typeId = TypeRegistry::InvalidType);
			~AttributeHolder();

			template <typename T>
			void setValue(T v);

			template <typename T>
			T getValue();

		private:
			template <typename T, bool isGreaterThanSizeOfPointer>
			struct ValueHolder;

		private:
			TypeRegistry::TypeId	mTypeId;
			ValueT					mValue;
		};

#include "attribute_holder.inl"

	}
}

#endif
