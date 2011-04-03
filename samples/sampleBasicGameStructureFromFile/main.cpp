#include <sfge/infrastructure/data_store.hpp>
#include <sfge/infrastructure/game.hpp>
#include <sfge/infrastructure/game_object.hpp>
#include <sfge/graphics/graphic_system.hpp>

#include "orbiter_behaviour.hpp"
#include "controller_chng_pos_color_behaviour.hpp"

using namespace std;
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
		DECLARE_BEHAVIOUR(OrbiterBehaviour);
	}

	virtual void OnEndSystemInit() override
	{
		GraphicSystem::getSingleton().Create(GraphicSystem::InitParams());

		LoadFile("data/sampleBasicGameStructure.json");

		SetupScene();
	}

private:

	void SetupScene()
	{
		DataStore &ds = DataStore::getSingleton();

		GameObjectPtr refGO = ds.InstantiateGameObjectDef("ControllableThing", "refObj");
		mObjects.push_back(refGO);

		GameObjectPtr orbiterGO = ds.InstantiateGameObjectDef("OrbitingThing");
		mObjects.push_back(orbiterGO);

		ds.InitializeInstances();
	}
};

int main(int argc, char **argv)
{
	SampleGame g;
	g.Run();

	return 0;
}
