#include "sfge/infrastructure/detail/attribute_holder.hpp"

#include <cstdlib>
#include <iostream>

using namespace std;

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
	if (mTypeInfo->IsBiggerThanPointer())
	{
		if (mTypeInfo->mHasCtorOrDtor)
			mTypeInfo->mDtor(mData.mValuePtr);
		else
			free(mData.mValuePtr);
	}

	cout << "Deleting AttributeHolder" << endl;
}

TypeRegistry::TypeId AttributeHolder::GetTypeId() const
{
	return mTypeInfo->mId;
}

}
}
