#include "sfge/infrastructure/type_registry.hpp"

#include <cassert>

using namespace std;

namespace sfge
{
	
TypeRegistry::TypeId				TypeRegistry::mNextId = 0;
TypeRegistry::TypeRegistryHolder	TypeRegistry::mContent;

void TypeRegistry::Init()
{
	RegisterType("sf::Vector2f");
}

TypeRegistry::TypeId TypeRegistry::RegisterType(const TypeName &typeName)
{
	TypeRegistryHolder::const_iterator it = mContent.find(typeName);
	if (it != mContent.end())
	{
		assert("Type already registered!" && it == mContent.end());
		return InvalidType;
	}

	TypeId tId = mNextId;
	mContent.insert(make_pair(typeName, mNextId++));
	return tId;
}

TypeRegistry::TypeId TypeRegistry::GetTypeIdFor(const TypeName &typeName)
{
	TypeRegistryHolder::const_iterator it = mContent.find(typeName);
	if (it == mContent.end())
	{
		assert("Type not registered!" && it == mContent.end());
		return InvalidType;
	}

	return it->second;
}

}
