#ifndef SFGE_INFRASTRUCTURE_VALUE_HOLDER_HPP
#define SFGE_INFRASTRUCTURE_VALUE_HOLDER_HPP

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
		class ValueHolder
		{
		public:
			static const ValueHolderPtr	InvalidHolderPtr;

		public:
			ValueHolder();

			template <typename T>
			explicit ValueHolder(const TypeRegistry::TypeInfo &typeInfo, const T *defaultVal = nullptr);
			template <typename T>
			explicit ValueHolder(const TypeRegistry::TypeInfo &typeInfo, const T &defaultVal);

			~ValueHolder();

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
			template <typename T>
			void Init(const TypeRegistry::TypeInfo &typeInfo, const T *defaultVal);

			//! Used to manipulate the value holder depending on size.
			template <typename T, bool isGreaterThanSizeOfPointer>
			struct TypeConverter;

			typedef void*	PointerT;
			typedef size_t	SmallTypeT;

		private:
			const TypeRegistry::TypeInfo * mTypeInfo;
			union Data
			{
				PointerT	mValuePtr;
				SmallTypeT	mValue;
			} mData;
		};

#include "value_holder.inl"

	}
}

#endif
