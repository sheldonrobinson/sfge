#include "sfge/infrastructure/data_store.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/behaviour.hpp"

#include <algorithm>

using namespace std;

namespace sfge
{

DataStore* DataStore::ms_Singleton = 0;

void DataStore::Init()
{
	new DataStore;
}

void DataStore::DeclareGameObjectDef(const std::string &godName)
{
	assert(mLinks.find(godName) == mLinks.end() && "GameObject already registered!");

	mLinks[godName] = BehaviourList();
}

void DataStore::DeclareBehaviourDef(const std::string &behaviourName, const BehaviourCreator &behaviourCreator)
{
	assert(mBehaviourDefinitions.find(behaviourName) == mBehaviourDefinitions.end() &&
		"Behaviour already registered!");

	mBehaviourDefinitions[behaviourName] = behaviourCreator;
}

void DataStore::LinkBehaviourDefToGameObjectDef(const std::string &godName, const std::string &behaviourName)
{
	LinkBehaviourDefToGameObjectDef(godName, behaviourName, Parameters());
}

void DataStore::LinkBehaviourDefToGameObjectDef(const std::string &godName, const std::string &behaviourName, const Parameters &defaultParams)
{
	assert(mLinks.find(godName) != mLinks.end() && "GameObject has not been registered!");

	mLinks[godName].insert(make_pair(behaviourName, defaultParams));
}

GameObjectPtr DataStore::InstantiateGameObjectDef(const std::string &godName)
{
	GameObjectPtr go(GameObject::Create());
	
	GOBehaviourLinks::const_iterator godIt = mLinks.find(godName);
	assert(godIt != mLinks.end() && "GameObject definition has no associated behaviours!");

	const BehaviourList &goBehaviours = godIt->second;
	for_each(goBehaviours.begin(), goBehaviours.end(),
		[&] (const BehaviourList::value_type &behaviourEntry) {
			go->AddBehaviour(InstantiateBehaviourDef(behaviourEntry.first, go, behaviourEntry.second));
		} );

	return go;
}

BehaviourPtr DataStore::InstantiateBehaviourDef(const std::string &behaviourName, GameObjectPtr owner, const Parameters &defaultParams)
{
	BehaviourDefs::const_iterator it = mBehaviourDefinitions.find(behaviourName);
	assert(it != mBehaviourDefinitions.end() && "Behaviour definition has not been registered!");

	return it->second(owner, defaultParams);
}

}
