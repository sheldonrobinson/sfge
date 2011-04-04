#include "sfge/infrastructure/detail/value_holder.hpp"

#include <cstdlib>
#include <iostream>

using namespace std;

namespace sfge
{
namespace detail
{

const ValueHolderPtr ValueHolder::InvalidHolderPtr(nullptr);

ValueHolder::ValueHolder()
	: mTypeInfo(&TypeRegistry::InvalidType)
{
}

ValueHolder::~ValueHolder()
{
	if (mTypeInfo->IsBiggerThanPointer())
	{
		if (mTypeInfo->mHasCtorOrDtor)
			mTypeInfo->mDtor(mData.mValuePtr);
		else
			free(mData.mValuePtr);
	}
}

TypeRegistry::TypeId ValueHolder::GetTypeId() const
{
	return mTypeInfo->mId;
}

}
}
