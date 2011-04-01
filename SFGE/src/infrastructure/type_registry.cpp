#include "sfge/infrastructure/type_registry.hpp"
#include "sfge/infrastructure/type_registration.hpp"

#include <cassert>

#include <SFML/System/Vector2.hpp>

using namespace std;

namespace sfge
{
	
const TypeRegistry::TypeInfo		TypeRegistry::InvalidType(TypeRegistry::InvalidTypeId, 0, false);
TypeRegistry::TypeId				TypeRegistry::mNextId = 0;

TypeRegistry::TypeRegistryHolder&	TypeRegistry::GetTypeRegistryHolder()
{
	static TypeRegistryHolder content;
	return content;
}

void TypeRegistry::RegisterType(const TypeName &typeName, size_t sizeType, bool hasCtorOrDtor, const CtorType &ctor)
{
	TypeRegistryHolder::const_iterator it = GetTypeRegistryHolder().find(typeName);
	if (it != GetTypeRegistryHolder().end())
	{
		assert("Type already registered!" && it == GetTypeRegistryHolder().end());
		return;
	}

	const TypeId tId = mNextId++;
	const TypeInfo tInfo(tId, sizeType, hasCtorOrDtor, ctor);
	GetTypeRegistryHolder().insert(make_pair(typeName, tInfo));
}

const TypeRegistry::TypeInfo& TypeRegistry::GetTypeInfoFor(const TypeName &typeName)
{
	TypeRegistryHolder::const_iterator it = GetTypeRegistryHolder().find(typeName);
	if (it == GetTypeRegistryHolder().end())
	{
		assert("Type not registered!" && it == GetTypeRegistryHolder().end());
		return InvalidType;
	}

	return it->second;
}

}
