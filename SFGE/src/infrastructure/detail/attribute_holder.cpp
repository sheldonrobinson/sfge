#include "sfge/infrastructure/detail/attribute_holder.hpp"

#include <cstdlib>

namespace sfge
{
namespace detail
{

const AttributeHolderPtr AttributeHolder::InvalidHolderPtr(0);

AttributeHolder::AttributeHolder()
	: mTypeInfo(TypeRegistry::InvalidType)
{
}

AttributeHolder::~AttributeHolder()
{
	// FIXME handle Dtors
	/*if (TypeRegistration<T>::isComplex)
	{
		T *p = reinterpret_cast<T*>(data.mValuePtr);
		p->~T();
	}*/
	
	if (mTypeInfo.IsBiggerThanPointer())
		free(mData.mValuePtr);
}

TypeRegistry::TypeId AttributeHolder::GetTypeId() const
{
	return mTypeInfo.mId;
}

}
}
