#include <sfge/infrastructure/data_store.hpp>
#include <sfge/infrastructure/game.hpp>
#include <sfge/graphics/graphic_system.hpp>

#include "orbiter_behaviour.hpp"

using namespace sfge;

class SampleGame : public Game
{
public:
	SampleGame()	{ ; }

protected:
	virtual void OnDeclareAdditionnalBehaviours() override
	{
		DECLARE_BEHAVIOUR(OrbiterBehaviour);
	}

	virtual void OnEndSystemInit() override
	{
		GraphicSystem::getSingleton().Create(GraphicSystem::InitParams());

		LoadWorld("sampleSolarSystem");
	}
};

int main(int argc, char **argv)
{
	SampleGame g;
	g.Run();

	return 0;
}
