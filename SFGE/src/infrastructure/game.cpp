#include "sfge/infrastructure/game.hpp"

#include "sfge/infrastructure/data_store.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/message_manager.hpp"
#include "sfge/infrastructure/type_registry.hpp"

#include "sfge/behaviours/render_behaviour.hpp"
#include "sfge/behaviours/transform_behaviour.hpp"

#include "sfge/graphics/graphic_system.hpp"

#include <algorithm>

#include <boost/property_tree/json_parser.hpp>

#include <SFML/System/Clock.hpp>

using namespace std;
using namespace boost;
using namespace boost::property_tree;

namespace sfge
{

Game::Game()
	: mQuitFlag(false)
{
}

Game::~Game()
{
}

void Game::Run()
{
	Init();
	
	GraphicSystem &gfxSys = GraphicSystem::getSingleton();

	sf::Clock clock;

	while(!mQuitFlag && GraphicSystem::getSingleton().IsMainWindowOpened())
	{
		gfxSys.UpdateEvents();
		gfxSys.PreRender();

		for_each(mObjects.begin(), mObjects.end(), [&] (GameObjectPtr go) { go->Update(clock.GetElapsedTime()); } );

		gfxSys.PostRender();
	}

	OnQuit();
}

void Game::Init()
{
	sfge::InitTypesStub();

	GraphicSystem::Init();
	MessageManager::Init();
	DataStore::Init();
	DeclareBehaviours();

	OnEndSystemInit();
}

void Game::DeclareBehaviours()
{
	// Declare built-in behaviours
	DECLARE_BEHAVIOUR(TransformBehaviour);
	DECLARE_BEHAVIOUR(RenderBehaviour);

	// Allow user to declare any additionnal behaviour
	OnDeclareAdditionnalBehaviours();
}

void Game::LoadFile(const std::string &fileName)
{
	Parameters content;
	json_parser::read_json(fileName, content);

	const std::string fileType = content.get("type", "");
	assert(!fileType.empty());

	if (fileType == "world")
	{
		LoadWorldFrom(content);
	}
}

#include <iostream>
void Game::LoadWorldFrom(const Parameters &content)
{
	DataStore &ds = DataStore::getSingleton();

	// Declare any game_object definitions required for the world
	cout << "Loading game_object_defs" << endl;
	ptree::const_assoc_iterator godIt = content.find("game_object_defs");
	if (godIt != content.not_found())
	{
		const ptree &godContent = godIt->second;
		cout << "Found: " << godContent.size() << endl;

		for_each(godContent.begin(), godContent.end(),
			[&] (const ptree::value_type &goDef)
			{
				// Check if the entry is just a reference to an already defined GO definition, or an embedded one
				const string &godName = goDef.second.data();
				if (!godName.empty())
				{
					assert(ds.IsGODRegistered(godName));
				}
				else
				{
					LoadGODefinitionFrom(goDef.second);
				}
			} );
	}

	cout << endl << "Loading game_object_instances" << endl;
	ptree::const_assoc_iterator goIt = content.find("game_object_instances");
	assert(goIt != content.not_found());

	const ptree &goContent = goIt->second;
	cout << "Found: " << goContent.size() << endl;

	for_each(goContent.begin(), goContent.end(),
		[&] (const ptree::value_type &goInstance)
		{
			// Check if the entry is just a reference to an already defined GO definition, or an embedded one
			const string &goDefName = goInstance.second.data();
			if (!goDefName.empty())
			{
				GameObjectPtr go = ds.InstantiateGameObjectDef(goDefName);
				mObjects.push_back(go);

				cout << "Instantiating " << goDefName << endl;
			}
			else // It's a named game object instance
			{
				const ptree &namedGO = goInstance.second;
				assert(namedGO.size() == 2);
				
				const string &goDefName		= namedGO.get("godName", "");
				const string &instanceName	= namedGO.get("instanceName", "");

				assert(!goDefName.empty() && !instanceName.empty());
				
				GameObjectPtr go = ds.InstantiateGameObjectDef(goDefName, instanceName);
				mObjects.push_back(go);

				cout << "Instantiating " << goDefName << " under the name '" << instanceName << "'" << endl;
			}
		} );
	
	cout << endl << "Finished loading world, initializing instances..." << endl;
	ds.InitializeInstances();

	cout << "Finished initialization" << endl;
}

void Game::LoadGODefinitionFrom(const Parameters &content)
{
	assert(content.data().empty());
	
	DataStore &ds = DataStore::getSingleton();
	
	const string &godName = content.get("name", "");
	cout << "Registering GO definition: " << godName << endl;
	ds.DeclareGameObjectDef(godName);

	cout << "Declaring behaviours";
	ptree::const_assoc_iterator behavioursIt = content.find("behaviours");
	assert(behavioursIt != content.not_found());

	const ptree &behavioursContent = behavioursIt->second;
	cout << " (found: " << behavioursContent.size() << ")" << endl;

	for_each(behavioursContent.begin(), behavioursContent.end(),
		[&] (const ptree::value_type &behaviourDecl)
		{
			// Check if the entry is just a reference to an already defined GO definition, or an embedded one
			const string &behaviourName = behaviourDecl.second.data();
			if (!behaviourName.empty())
			{
				assert(ds.IsBehaviourRegistered(behaviourName));
				cout << behaviourName << endl;
				ds.LinkBehaviourDefToGameObjectDef(godName, behaviourName);
			}
			else // It's a compound behaviour declaration (ie, it embeds some init parameters)
			{
				const string &behaviourName = behaviourDecl.second.get("name", "");
				assert(ds.IsBehaviourRegistered(behaviourName));
				cout << behaviourName << endl;
				
				const ptree::const_assoc_iterator paramsIt = behaviourDecl.second.find("params");
				assert(paramsIt != behaviourDecl.second.not_found());
				
				ds.LinkBehaviourDefToGameObjectDef(godName, behaviourName, paramsIt->second);
			}
		} );
}

}
