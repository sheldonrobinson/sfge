#ifndef SFGE_INFRASTRUCTURE_DATA_STORE_HPP
#define SFGE_INFRASTRUCTURE_DATA_STORE_HPP

#include <map>
#include <string>

#include "sfge/utilities/singleton.hpp"
#include "sfge/utilities/delegate.hpp"
#include "sfge/infrastructure/infrastructure_fwd.hpp"

namespace sfge
{
	class DataStore : public Singleton<DataStore>
	{
	public:
		typedef delegate<BehaviourPtr(GameObjectPtr)>	BehaviourCreator;

	public:
		static void Init();

		// Data types registration
		void DeclareGameObjectDef(const std::string &godName);
		void DeclareBehaviourDef(const std::string &behaviourName, const BehaviourCreator &behaviourCreator);
		void LinkBehaviourDefToGameObjectDef(const std::string &godName, const std::string &behaviourName);
		void LinkBehaviourDefToGameObjectDef(const std::string &godName, const std::string &behaviourName, const Parameters &defaultParams);

		// Instantiation
		//! This will create a new GameObject based on definition registered as godName. The instance name is optionnal, but anonymous instances can't be get back.
		GameObjectPtr InstantiateGameObjectDef(const std::string &godName, const std::string &goInstanceName = "");

		//! This method will send the default params to every instanciated behaviour.
		void InitializeInstances();

		// Getters
		GameObjectPtr GetGameObjectInstanceByName(const std::string &goInstanceName);

	private:
		typedef std::map<std::string,	BehaviourCreator>		BehaviourDefs;
		typedef std::map<std::string,	Parameters>				BehaviourList;
		typedef std::map<std::string,	BehaviourList>			GOBehaviourLinks;
		typedef std::map<Behaviour*,	const Parameters*>		BehavioursToInit;
		typedef std::map<std::string,	GameObjectPtr>			GameObjectInstances;

	private:
		BehaviourPtr InstantiateBehaviourDef(const std::string &behaviourName, GameObjectPtr owner);

	private:
		BehaviourDefs		mBehaviourDefinitions;
		GOBehaviourLinks	mLinks;
		BehavioursToInit	mBehavioursWaitingForInit;
		GameObjectInstances	mInstances;
	};

	template <typename T>
	BehaviourPtr create(GameObjectPtr owner) { return BehaviourPtr(new T(owner)); }

	// This macro may be used to declare a behaviour without having to type all the bloat around. Should remove bloat heh?
#define DECLARE_BEHAVIOUR(DataStoreInstance, Behaviour) DataStoreInstance.DeclareBehaviourDef(#Behaviour, DataStore::BehaviourCreator::from_function<create<Behaviour>>());
}

#endif
