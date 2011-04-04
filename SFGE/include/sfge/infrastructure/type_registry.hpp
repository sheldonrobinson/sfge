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
		typedef void *(*Ctor)(const void*);					//!< Parameter is an optionnal default value to copy from.
		typedef void *(*PlacemtCtor)(void*, const void*);	//!< Parameters are Where and an optionnal default value to copy from.
		typedef void  (*Dtor)(void*);

		struct TypeInfo
		{
			TypeInfo(TypeId id, TypeSize size, bool hasCtorOrDtor)
				:	mId(id), mSize(size), mHasCtorOrDtor(hasCtorOrDtor),
					mPlacementCtor(nullptr), mDtor(nullptr)
			{
			}

			bool IsBiggerThanPointer() const				{ return mSize > sizeof(void*); }
			bool operator==(const TypeInfo &other) const	{ return mId == other.mId; }

			TypeId		mId;
			TypeSize	mSize;
			bool		mHasCtorOrDtor;
			Ctor		mDefaultCtor;
			PlacemtCtor	mPlacementCtor;
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
