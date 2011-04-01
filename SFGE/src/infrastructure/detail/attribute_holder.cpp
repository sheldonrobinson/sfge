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
	// FIXME handle alignment
	if (mTypeInfo.IsBiggerThanPointer())
		mData.mValuePtr = malloc(mTypeInfo.mSize);

	// FIXME handle Ctors
	if (typeInfo.mHasCtorOrDtor)
	{
		/*if (typeInfo.IsBiggerThanPointer())
			new (mData.mValuePtr) T();
		else
			ValueHolder<T, false>::Store(mData, T());*/
	}
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
