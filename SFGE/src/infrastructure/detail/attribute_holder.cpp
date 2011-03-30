#include "sfge/infrastructure/detail/attribute_holder.hpp"

#include <cstdlib>

namespace sfge
{
namespace detail
{

const AttributeHolderPtr AttributeHolder::InvalidHolderPtr(0);

AttributeHolder::AttributeHolder(const TypeRegistry::TypeInfo &typeInfo)
	: mTypeInfo(typeInfo), mValue(0)
{
	if (mTypeInfo.second > sizeof(void*))
		mValue = malloc(mTypeInfo.second);
}

AttributeHolder::~AttributeHolder()
{
	free(mValue);
}

TypeRegistry::TypeId AttributeHolder::GetTypeId() const
{
	return mTypeInfo.first;
}

}
}
