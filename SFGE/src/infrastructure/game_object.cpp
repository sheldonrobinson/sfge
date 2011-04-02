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
	RegisterAttribute<sf::Vector2f>(AK_GO_POSITION);
}

GameObject::~GameObject()
{
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
