#ifndef SFGE_INFRASTRUCTURE_ATTRIBUTE_HOLDER_HPP
#define SFGE_INFRASTRUCTURE_ATTRIBUTE_HOLDER_HPP

#include <cassert>
#include <memory>

#include <SFML/Config.hpp>

#include "sfge/infrastructure/infrastructure_fwd.hpp"
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
			static const AttributeHolderPtr	InvalidHolderPtr;

		public:
			AttributeHolder(const TypeRegistry::TypeInfo &typeInfo = TypeRegistry::InvalidType);
			~AttributeHolder();

			TypeRegistry::TypeId	GetTypeId() const;

			template <typename T>
			void SetValue(const T &v);

			template <typename T>
			const T& GetValue() const;


		private:
			template <typename T, bool isGreaterThanSizeOfPointer>
			struct ValueHolder;

		private:
			TypeRegistry::TypeInfo	mTypeInfo;
			ValueT					mValue;
		};

#include "attribute_holder.inl"

	}
}

#endif
