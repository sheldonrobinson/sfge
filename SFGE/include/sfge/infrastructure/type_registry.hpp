#ifndef SFGE_INFRASTRUCTURE_TYPE_REGISTRY_HPP
#define SFGE_INFRASTRUCTURE_TYPE_REGISTRY_HPP

#include <cassert>
#include <map>
#include <string>

namespace sfge
{
	class TypeRegistry
	{
	public:
		typedef size_t				TypeId;
		typedef size_t				TypeSize;
		typedef std::string			TypeName;
		typedef void *(*Ctor)(void*);
		typedef void  (*Dtor)(void*);

		struct TypeInfo
		{
			TypeInfo(TypeId id, TypeSize size, bool hasCtorOrDtor)
				:	mId(id), mSize(size), mHasCtorOrDtor(hasCtorOrDtor),
					mCtor(nullptr), mDtor(nullptr)
			{
			}

			bool IsBiggerThanPointer() const	{ return mSize > sizeof(void*); }

			TypeId		mId;
			TypeSize	mSize;
			bool		mHasCtorOrDtor;
			Ctor		mCtor;
			Dtor		mDtor;

		private:
			TypeInfo();
		};

	public:
		static const TypeId		InvalidTypeId	= ~0;
		static const TypeInfo	InvalidType;

	public:
		template <typename T>
		static void				RegisterType	(const TypeName &typeName, size_t sizeType, bool hasCtorOrDtor);
		static const TypeInfo&	GetTypeInfoFor	(const TypeName &typeName);

	private:
		typedef std::map<TypeName, TypeInfo> TypeRegistryHolder;

	private:
		static TypeRegistryHolder&	GetTypeRegistryHolder();

	private:
		static TypeId				mNextId;
	};

#include "type_registry.inl"
}

#endif
