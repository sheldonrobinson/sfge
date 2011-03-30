#include <sfge/infrastructure/game.hpp>
#include <sfge/graphics/graphic_system.hpp>

using namespace sfge;

class SampleGame : public Game
{
public:
	SampleGame()	{ ; }

protected:
	virtual void OnEndSystemInit()
	{
		GraphicSystem::getSingleton().Create(GraphicSystem::InitParams());
	}
};

int main(int argc, char **argv)
{
	SampleGame g;
	g.Run();

	return 0;
}
