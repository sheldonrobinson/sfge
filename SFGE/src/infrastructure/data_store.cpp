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
	assert(mLinks.find(godName) == mLinks.end() && ("GameObject definition named " + godName + " has already been registered!").c_str());

	mLinks[godName] = BehaviourList();
}

void DataStore::DeclareBehaviourDef(const std::string &behaviourName, const BehaviourCreator &behaviourCreator)
{
	assert(mBehaviourDefinitions.find(behaviourName) == mBehaviourDefinitions.end() &&
		("Behaviour definition named " + behaviourName + " has already been registered!").c_str());

	mBehaviourDefinitions[behaviourName] = behaviourCreator;
}

void DataStore::LinkBehaviourDefToGameObjectDef(const std::string &godName, const std::string &behaviourName)
{
	LinkBehaviourDefToGameObjectDef(godName, behaviourName, Parameters());
}

void DataStore::LinkBehaviourDefToGameObjectDef(const std::string &godName, const std::string &behaviourName, const Parameters &defaultParams)
{
	assert(mLinks.find(godName) != mLinks.end() && ("GameObject definition named " + godName + " has not been registered!").c_str());

	mLinks[godName].insert(make_pair(behaviourName, defaultParams));
}

GameObjectPtr DataStore::InstantiateGameObjectDef(const std::string &godName, const std::string &goInstanceName)
{
	GameObjectPtr go(GameObject::Create());
	
	GOBehaviourLinks::const_iterator godIt = mLinks.find(godName);
	assert(godIt != mLinks.end() && ("GameObject definition named " + godName + " has no associated behaviours!").c_str());
	
	const BehaviourList &goBehaviours = godIt->second;
	for_each(goBehaviours.begin(), goBehaviours.end(),
		[&] (const BehaviourList::value_type &behaviourEntry) {
			BehaviourPtr bp = InstantiateBehaviourDef(behaviourEntry.first, go);
			mBehavioursWaitingForInit.insert(make_pair(bp.get(), &behaviourEntry.second));
			go->AddBehaviour(bp);
		} );

	if (!goInstanceName.empty())
		mInstances.insert(make_pair(goInstanceName, go));

	return go;
}

BehaviourPtr DataStore::InstantiateBehaviourDef(const std::string &behaviourName, GameObjectPtr owner)
{
	BehaviourDefs::const_iterator it = mBehaviourDefinitions.find(behaviourName);
	assert(it != mBehaviourDefinitions.end() && ("No Behaviour definition named " + behaviourName + " has been registered!").c_str());

	return it->second(owner);
}

void DataStore::InitializeInstances()
{
	for_each(mBehavioursWaitingForInit.begin(), mBehavioursWaitingForInit.end(),
		[&] (BehavioursToInit::value_type &entry) { entry.first->OnParamsReceived(*entry.second); } );
}

GameObjectPtr DataStore::GetGameObjectInstanceByName(const std::string &goInstanceName)
{
	if (goInstanceName.empty())
		return GameObjectPtr();

	GameObjectInstances::const_iterator it = mInstances.find(goInstanceName);
	assert(it != mInstances.end() && ("Failed to retrieve instance named " + goInstanceName).c_str());
	return it->second;
}

}
