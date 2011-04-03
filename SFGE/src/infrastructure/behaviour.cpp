#include "sfge/infrastructure/behaviour.hpp"
#include "sfge/infrastructure/game_object.hpp"

#include <iostream>

using namespace std;

namespace sfge
{

Behaviour::Behaviour(GameObjectWeakPtr owner)
	: mOwner(owner)
{
}

Behaviour::~Behaviour()
{
}

void Behaviour::SetOwner(GameObjectWeakPtr owner)
{
	mOwner = owner;
}

}
