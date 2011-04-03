#include <sfge/infrastructure/data_store.hpp>
#include <sfge/infrastructure/game.hpp>
#include <sfge/infrastructure/game_object.hpp>
#include <sfge/graphics/graphic_system.hpp>

#include "controller_chng_pos_color_behaviour.hpp"

using namespace sf;
using namespace sfge;

class SampleGame : public Game
{
public:
	SampleGame()	{ ; }

protected:
	virtual void OnDeclareAdditionnalBehaviours() override
	{
		DECLARE_BEHAVIOUR(ControllerBehaviour);
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
		refObjDrawableDef.put("type",	"shape");
		refObjDrawableDef.put("shape",	"circle");
		refObjDrawableDef.put("cx",		0);
		refObjDrawableDef.put("cy",		0);
		refObjDrawableDef.put("radius", 50);
		refObjDrawableDef.put("cr",		Color::Magenta.r);
		refObjDrawableDef.put("cg",		Color::Magenta.g);
		refObjDrawableDef.put("cb",		Color::Magenta.b);
		refObjDrawableDef.put("ca",		Color::Magenta.a);

		// Declare the 2 gameobject definitions we need
		DataStore &ds = DataStore::getSingleton();

		ds.DeclareGameObjectDef("ControllableThing");

		// Create the links between gameobject definitions and registered behaviours (eventually settings some default params)
		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "TransformBehaviour");
		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "ControllerBehaviour");
		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "RenderBehaviour",	refObjDrawableDef);
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
