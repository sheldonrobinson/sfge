#include <sfge/infrastructure/data_store.hpp>
#include <sfge/infrastructure/game.hpp>
#include <sfge/graphics/graphic_system.hpp>

#include "sorlo_input_behaviour.hpp"

using namespace sfge;

class SampleGame : public Game
{
public:
	SampleGame()	{ ; }

protected:
	virtual void OnDeclareAdditionnalBehaviours() override
	{
		DECLARE_BEHAVIOUR(SorloInputBehaviour);
	}

	virtual void OnEndSystemInit() override
	{
		GraphicSystem::getSingleton().Create(GraphicSystem::InitParams());

		LoadWorld("sampleSpriteAnimation");
	}
};

int main(int argc, char **argv)
{
	SampleGame g;
	g.Run();

	return 0;
}
