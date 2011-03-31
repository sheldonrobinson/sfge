#include "sfge/infrastructure/detail/attribute_holder.hpp"

#include <cstdlib>

namespace sfge
{
namespace detail
{

const AttributeHolderPtr AttributeHolder::InvalidHolderPtr(0);

AttributeHolder::AttributeHolder(const TypeRegistry::TypeInfo &typeInfo)
	: mTypeInfo(typeInfo)
{
	if (mTypeInfo.mSize > sizeof(void*))
		mData.mValuePtr = malloc(mTypeInfo.mSize);
}

AttributeHolder::~AttributeHolder()
{
	free(mData.mValuePtr);
}

TypeRegistry::TypeId AttributeHolder::GetTypeId() const
{
	return mTypeInfo.mId;
}

}
}
