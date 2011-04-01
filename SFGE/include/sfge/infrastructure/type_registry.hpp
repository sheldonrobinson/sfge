#ifndef SFGE_INFRASTRUCTURE_TYPE_REGISTRY_HPP
#define SFGE_INFRASTRUCTURE_TYPE_REGISTRY_HPP

#include <map>
#include <string>

#include <boost/static_assert.hpp>

#include "sfge/utilities/delegate.hpp"

namespace sfge
{
	class TypeRegistry
	{
	public:
		typedef size_t				TypeId;
		typedef size_t				TypeSize;
		typedef std::string			TypeName;
		typedef delegate<void()>	CtorType;

		struct TypeInfo
		{
			TypeInfo(TypeId id, TypeSize size, bool hasCtorOrDtor, const CtorType &ctor = CtorType())
				:	mId(id), mSize(size), mHasCtorOrDtor(hasCtorOrDtor), mTypeCtor(ctor)
			{
			}

			bool IsBiggerThanPointer() const	{ return mSize > sizeof(void*); }

			TypeId		mId;
			TypeSize	mSize;
			bool		mHasCtorOrDtor;
			CtorType	mTypeCtor;

		private:
			TypeInfo();
		};

	public:
		static const TypeId		InvalidTypeId	= ~0;
		static const TypeInfo	InvalidType;

	public:
		static void				RegisterType	(const TypeName &typeName, size_t sizeType, bool hasCtorOrDtor, const CtorType &ctor = CtorType());
		static const TypeInfo&	GetTypeInfoFor	(const TypeName &typeName);

	private:
		typedef std::map<TypeName, TypeInfo> TypeRegistryHolder;

	private:
		static TypeRegistryHolder&	GetTypeRegistryHolder();

	private:
		static TypeId				mNextId;
	};
}

#endif
