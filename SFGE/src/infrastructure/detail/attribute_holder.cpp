#include "sfge/infrastructure/detail/attribute_holder.hpp"

namespace sfge
{
namespace detail
{

const AttributeHolderPtr AttributeHolder::InvalidHolderPtr(0);

AttributeHolder::AttributeHolder(TypeRegistry::TypeId typeId)
	: mTypeId(typeId)
{
}

AttributeHolder::~AttributeHolder()
{
}

TypeRegistry::TypeId AttributeHolder::GetTypeId() const
{
	return mTypeId;
}

}
}
