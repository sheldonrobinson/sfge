#include "sfge/infrastructure/behaviour.hpp"
#include "sfge/infrastructure/game_object.hpp"

namespace sfge
{

Behaviour::Behaviour(GameObjectPtr owner)
	: mOwner(owner)
{
}

Behaviour::~Behaviour()
{
}

void Behaviour::RegisterAttribute(size_t attributeKey, const TypeRegistry::TypeInfo &typeInfo)
{
	return mOwner->RegisterAttribute(attributeKey, typeInfo);
}

}
