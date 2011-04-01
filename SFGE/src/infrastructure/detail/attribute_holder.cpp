#include "sfge/infrastructure/detail/attribute_holder.hpp"

#include <cstdlib>

namespace sfge
{
namespace detail
{

const AttributeHolderPtr AttributeHolder::InvalidHolderPtr(nullptr);

AttributeHolder::AttributeHolder()
	: mTypeInfo(&TypeRegistry::InvalidType)
{
}

AttributeHolder::~AttributeHolder()
{
	if (mTypeInfo->mHasCtorOrDtor)
	{
		mTypeInfo->mDtor(mData.mValuePtr);
	}
	
	if (mTypeInfo->IsBiggerThanPointer())
		free(mData.mValuePtr);
}

TypeRegistry::TypeId AttributeHolder::GetTypeId() const
{
	return mTypeInfo->mId;
}

}
}
