#include "sfge/infrastructure/game_object.hpp"

#include "sfge/infrastructure/detail/attribute_holder.hpp"
#include "sfge/infrastructure/behaviour.hpp"

#include <algorithm>
#include <cassert>

using namespace std;

namespace sfge
{
	
GameObjectPtr GameObject::Create()
{
	GameObjectPtr go(new GameObject());
	return go;
}

GameObject::GameObject()
{
	const TypeRegistry::TypeId vec2fId = TypeRegistry::GetTypeIdFor("sf::Vector2f");
	POSITION_ATTRIBUTE = RegisterAttribute(vec2fId);
}

GameObject::~GameObject()
{
}

size_t GameObject::RegisterAttribute(const TypeRegistry::TypeId typeId)
{
	const size_t attributeId = mAttributes.size();

	detail::AttributeHolderPtr posHolder(new detail::AttributeHolder(typeId));
	mAttributes.insert(make_pair(attributeId, posHolder));

	return attributeId;
}

void GameObject::AddBehaviour(BehaviourPtr b)
{
	mBehaviours.push_back(b);
}

void GameObject::Update(float dt)
{
	for_each(mBehaviours.begin(), mBehaviours.end(), [&] (BehaviourPtr b) { b->OnUpdate(dt); } );
}

}
