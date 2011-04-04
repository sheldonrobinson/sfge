#include "sfge/infrastructure/data_store.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/behaviour.hpp"
#include "sfge/utilities/null_deleter.hpp"

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

	mLinks[godName] = BehaviourParameters();
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

GameObjectPtr DataStore::InstantiateGameObjectDef(const std::string &godName, const std::string &goInstanceName, const BehaviourParameters &instanceParameters)
{
	GameObjectPtr go(GameObject::Create());
	
	GOBehaviourLinks::const_iterator godIt = mLinks.find(godName);
	if (godIt == mLinks.end())
		throw Exception("GameObject definition named " + godName + " doesn't exist!");
	
	const BehaviourParameters &goBehaviours = godIt->second;
	for_each(goBehaviours.begin(), goBehaviours.end(),
		[&] (const BehaviourParameters::value_type &behaviourEntry)
		{
			BehaviourPtr bp = InstantiateBehaviour(behaviourEntry.first, go);

			DataStore::BehaviourParameters::const_iterator instParams = instanceParameters.find(behaviourEntry.first);

			if (instParams == instanceParameters.end())
			{
				mBehavioursWaitingForInit.insert(make_pair(bp.get(), ParametersConstPtr(&behaviourEntry.second, null_deleter())));
			}
			else
			{
				ParametersConstPtr mergedParams = MergeDefaultAndInstanceParams(behaviourEntry.second, instParams->second);
				mBehavioursWaitingForInit.insert(make_pair(bp.get(), mergedParams));
			}

			go->AddBehaviour(bp);
		} );

	if (!goInstanceName.empty())
		mInstances.insert(make_pair(goInstanceName, go));

	return go;
}

BehaviourPtr DataStore::InstantiateBehaviour(const std::string &behaviourName, GameObjectWeakPtr owner)
{
	BehaviourDefs::const_iterator it = mBehaviourDefinitions.find(behaviourName);
	if (it == mBehaviourDefinitions.end())
		throw Exception("No Behaviour definition named " + behaviourName + " has been registered!");

	return it->second(owner);
}

ParametersPtr DataStore::MergeDefaultAndInstanceParams(const Parameters &defaultParams, const Parameters &instanceParams)
{
	ParametersPtr out(new Parameters(defaultParams));

	for_each(instanceParams.ordered_begin(), instanceParams.not_found(),
		[&] (const Parameters::value_type &entry)
		{
			Parameters::assoc_iterator it = out->find(entry.first);
			if (it != out->not_found())
				it->second = entry.second;
			else
			{
				if (entry.second.data().empty())
					throw Exception("Malformed instance parameters '" + entry.first + "'");
				out->put(entry.first, entry.second.data());
			}
		} );

	return out;
}

void DataStore::InitializeInstances()
{
	for_each(mBehavioursWaitingForInit.begin(), mBehavioursWaitingForInit.end(),
		[&] (BehavioursToInit::value_type &entry) { entry.first->OnParamsReceived(*entry.second); } );
}

GameObjectWeakPtr DataStore::GetGameObjectInstanceByName(const std::string &goInstanceName)
{
	if (goInstanceName.empty())
		return GameObjectPtr();

	GameObjectInstances::const_iterator it = mInstances.find(goInstanceName);
	if (it == mInstances.end())
		throw Exception("Failed to retrieve instance named " + goInstanceName);
	return it->second;
}

}
