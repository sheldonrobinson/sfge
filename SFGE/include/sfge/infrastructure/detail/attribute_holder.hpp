#ifndef SFGE_INFRASTRUCTURE_ATTRIBUTE_HOLDER_HPP
#define SFGE_INFRASTRUCTURE_ATTRIBUTE_HOLDER_HPP

#include <cassert>
#include <memory>

#include <SFML/Config.hpp>

#include "sfge/infrastructure/infrastructure_fwd.hpp"
#include "sfge/infrastructure/type_registry.hpp"
#include "sfge/infrastructure/type_registration.hpp"
#include "sfge/infrastructure/type_registration_impl.hpp"

namespace sfge
{
	namespace detail
	{
		class AttributeHolder
		{
		public:
			static const AttributeHolderPtr	InvalidHolderPtr;

		public:
			AttributeHolder();

			template <typename T>
			explicit AttributeHolder(const TypeRegistry::TypeInfo &typeInfo, const T &defaultVal);
			~AttributeHolder();

			TypeRegistry::TypeId GetTypeId() const;

			template <typename T>
			void SetValue(const T &v);

			template <typename T>
			const T& GetValue() const;

			template <typename T>
			T& GetValue();

		private:
			template <typename T>
			void CheckTypes() const;

		private:
			//! Used to manipulate the value holder depending on size.
			template <typename T, bool isGreaterThanSizeOfPointer>
			struct ValueHolder;

		private:
			const TypeRegistry::TypeInfo * const mTypeInfo;
			union Data
			{
				void*			mValuePtr;
				unsigned int	mValue;
			} mData;
		};

#include "attribute_holder.inl"

	}
}

#endif
