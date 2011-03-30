#ifndef SFGE_INFRASTRUCTURE_TYPE_REGISTRY_HPP
#define SFGE_INFRASTRUCTURE_TYPE_REGISTRY_HPP

#include <map>
#include <string>

namespace sfge
{
	class TypeRegistry
	{
	public:
		typedef size_t			TypeId;
		typedef std::string		TypeName;

	public:
		static const TypeId		InvalidType = ~0;

	public:
		static void Init();

		static TypeId RegisterType(const TypeName &typeName);
		static TypeId GetTypeIdFor(const TypeName &typeName);

	private:
		typedef std::map<TypeName, TypeId> TypeRegistryHolder;

	private:
		static TypeId				mNextId;
		static TypeRegistryHolder	mContent;
	};
}

#endif
