#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/behaviours.hpp"

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

void GameObject::Update(float dt)
{
}


}
