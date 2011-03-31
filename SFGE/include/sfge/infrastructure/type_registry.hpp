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
			TypeInfo(TypeId id, TypeSize size)
				: mId(id), mSize(size)
			{
			}
			TypeId		mId;
			TypeSize	mSize;
		};

	public:
		static const TypeId		InvalidTypeId	= ~0;
		static const TypeInfo	InvalidType;

	public:
		static void				RegisterType	(const TypeName &typeName, size_t sizeType);
		static const TypeInfo&	GetTypeInfoFor	(const TypeName &typeName);

	private:
		typedef std::map<TypeName, TypeInfo> TypeRegistryHolder;

	private:
		static TypeId				mNextId;
		static TypeRegistryHolder	mContent;
	};
}

#endif
