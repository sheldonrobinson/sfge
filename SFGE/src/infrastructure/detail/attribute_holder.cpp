#include "sfge/infrastructure/detail/attribute_holder.hpp"

namespace sfge
{
namespace detail
{

const AttributeHolderPtr AttributeHolder::InvalidHolderPtr(0);

AttributeHolder::AttributeHolder(const TypeRegistry::TypeInfo &typeInfo)
	: mTypeInfo(typeInfo)
{
}

AttributeHolder::~AttributeHolder()
{
}

TypeRegistry::TypeId AttributeHolder::GetTypeId() const
{
	return mTypeInfo.first;
}

}
}
