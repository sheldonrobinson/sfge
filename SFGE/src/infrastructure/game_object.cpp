#include "sfge/infrastructure/game_object.hpp"

#include "sfge/infrastructure/behaviour.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"

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
	const TypeRegistry::TypeInfo &vec2fInfo	= TypeRegistry::GetTypeInfoFor("sf::Vector2f");
	RegisterAttribute(AK_GO_POSITION, vec2fInfo);
}

GameObject::~GameObject()
{
}

void GameObject::RegisterAttribute(size_t attributeKey, const TypeRegistry::TypeInfo &typeInfo)
{
	assert(mAttributes.find(attributeKey) == mAttributes.end() && "Attribute key already registered!");

	detail::AttributeHolderPtr posHolder(new detail::AttributeHolder(typeInfo));
	mAttributes.insert(make_pair(attributeKey, posHolder));
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
