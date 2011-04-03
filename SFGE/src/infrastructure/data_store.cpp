#include "sfge/infrastructure/data_store.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/behaviour.hpp"

#include <algorithm>
#include <exception>

using namespace std;

namespace sfge
{

namespace
{
	class Exception : public std::exception
	{
	public:
		Exception(const std::string &text)
			: mText(text)
		{
		}

		virtual const char *what() const override
		{
			return mText.c_str();
		}

	private:
		std::string mText;
	};
}

DataStore* DataStore::ms_Singleton = 0;

void DataStore::Init()
{
	new DataStore;
}

void DataStore::ClearAll()
{
	mLinks.clear();
	mBehavioursWaitingForInit.clear();
	mInstances.clear();
}

void DataStore::DeclareGameObjectDef(const std::string &godName)
{
	if (mLinks.find(godName) != mLinks.end())
		throw Exception("GameObject definition named " + godName + " has already been registered!");

	mLinks[godName] = BehaviourList();
}

void DataStore::DeclareBehaviourDef(const std::string &behaviourName, const BehaviourCreator &behaviourCreator)
{
	if (mBehaviourDefinitions.find(behaviourName) != mBehaviourDefinitions.end())
		throw Exception("Behaviour definition named " + behaviourName + " has already been registered!");

	mBehaviourDefinitions[behaviourName] = behaviourCreator;
}

void DataStore::LinkBehaviourDefToGameObjectDef(const std::string &godName, const std::string &behaviourName)
{
	LinkBehaviourDefToGameObjectDef(godName, behaviourName, Parameters());
}

void DataStore::LinkBehaviourDefToGameObjectDef(const std::string &godName, const std::string &behaviourName, const Parameters &defaultParams)
{
	if (mLinks.find(godName) == mLinks.end())
		throw Exception("GameObject definition named " + godName + " has not been registered!");

	mLinks[godName].insert(make_pair(behaviourName, defaultParams));
}

bool DataStore::IsGODRegistered(const std::string &godName) const
{
	return mLinks.find(godName) != mLinks.end();
}

bool DataStore::IsBehaviourRegistered(const std::string &behaviourName) const
{
	return mBehaviourDefinitions.find(behaviourName) != mBehaviourDefinitions.end();
}

GameObjectPtr DataStore::InstantiateGameObjectDef(const std::string &godName, const std::string &goInstanceName)
{
	GameObjectPtr go(GameObject::Create());
	
	GOBehaviourLinks::const_iterator godIt = mLinks.find(godName);
	if (godIt == mLinks.end())
		throw Exception("GameObject definition named " + godName + " doesn't exist!");
	
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
	if (it == mBehaviourDefinitions.end())
		throw Exception("No Behaviour definition named " + behaviourName + " has been registered!");

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
	if (it == mInstances.end())
		throw Exception("Failed to retrieve instance named " + goInstanceName);
	return it->second;
}

}
