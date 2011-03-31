#include "sfge/infrastructure/type_registry.hpp"
#include "sfge/infrastructure/type_registration.hpp"

#include <cassert>

#include <SFML/System/Vector2.hpp>

using namespace std;

namespace sfge
{
	
const TypeRegistry::TypeInfo		TypeRegistry::InvalidType(TypeRegistry::InvalidTypeId, 0);

TypeRegistry::TypeId				TypeRegistry::mNextId = 0;
TypeRegistry::TypeRegistryHolder	TypeRegistry::mContent;

void TypeRegistry::RegisterType(const TypeName &typeName, size_t sizeType)
{
	TypeRegistryHolder::const_iterator it = mContent.find(typeName);
	if (it != mContent.end())
	{
		assert("Type already registered!" && it == mContent.end());
		return;
	}

	const TypeId tId = mNextId++;
	const TypeInfo tInfo(tId, sizeType);
	mContent.insert(make_pair(typeName, tInfo));
}

const TypeRegistry::TypeInfo& TypeRegistry::GetTypeInfoFor(const TypeName &typeName)
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
