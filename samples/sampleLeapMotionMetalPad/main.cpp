#include <sfge/infrastructure/data_store.hpp>
#include <sfge/infrastructure/game.hpp>
#include <sfge/infrastructure/game_object.hpp>
#include <sfge/graphics/graphic_system.hpp>

#include "controller_leap_metalpad.hpp"

using namespace sf;
using namespace sfge;

class SampleGame : public Game
{
public:
	SampleGame()	{ ; }

protected:
	virtual void OnDeclareAdditionnalBehaviours() override
	{
		DECLARE_BEHAVIOUR(ControllerLeapMetalPad);
	}

	virtual void OnEndSystemInit() override
	{
		GraphicSystem::getSingleton().Create(GraphicSystem::InitParams());

		// NB: this step is generally done by loading data files.
		SetupDataStore();

		SetupScene();
	}

private:
	void SetupDataStore()
	{
		// Setup some parameters
		Parameters refObjDrawableDef;
		refObjDrawableDef.put("shape",	"circle");
		refObjDrawableDef.put("radius", 50);

		// Declare the 2 gameobject definitions we need
		DataStore &ds = DataStore::getSingleton();

		ds.DeclareGameObjectDef("ControllableThing");

		// Create the links between gameobject definitions and registered behaviours (eventually settings some default params)
		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "TransformBehaviour");
		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "ControllerLeapMetalPad");
		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "RenderShapeBehaviour",	refObjDrawableDef);
	}

	void SetupScene()
	{
		DataStore &ds = DataStore::getSingleton();

		GameObjectPtr refGO = ds.InstantiateGameObjectDef("ControllableThing", "refObj");
		mObjects.push_back(refGO);

		ds.InitializeInstances();
	}
};

int main(int argc, char **argv)
{
	SampleGame g;
	g.Run();

	return 0;
}
