#ifndef SFGE_INFRASTRUCTURE_TYPE_REGISTRY_HPP
#define SFGE_INFRASTRUCTURE_TYPE_REGISTRY_HPP

#include <map>
#include <string>

#include <boost/static_assert.hpp>

namespace sfge
{
	class TypeRegistry
	{
	public:
		typedef size_t			TypeId;
		typedef size_t			TypeSize;
		typedef std::string		TypeName;

		struct TypeInfo
		{
			TypeInfo(TypeId id, TypeSize size, bool hasCtorOrDtor)
				:	mId(id), mSize(size), mHasCtorOrDtor(hasCtorOrDtor)
			{
			}

			bool IsBiggerThanPointer() const	{ return mSize > sizeof(void*); }

			TypeId		mId;
			TypeSize	mSize;
			bool		mHasCtorOrDtor;

		private:
			TypeInfo();
		};

	public:
		static const TypeId		InvalidTypeId	= ~0;
		static const TypeInfo	InvalidType;

	public:
		static void				RegisterType	(const TypeName &typeName, size_t sizeType, bool hasCtorOrDtor);
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
