#include "sfge/infrastructure/detail/attribute_holder.hpp"

namespace sfge
{
namespace detail
{

AttributeHolder::AttributeHolder(TypeRegistry::TypeId typeId)
	: mTypeId(typeId)
{
}

AttributeHolder::~AttributeHolder()
{
}

}
}
