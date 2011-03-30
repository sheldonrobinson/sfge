#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/behaviour.hpp"

#include <algorithm>

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
