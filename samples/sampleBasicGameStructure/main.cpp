#include <iostream>

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/game.hpp>
#include <sfge/infrastructure/game_object.hpp>
#include <sfge/graphics/graphic_system.hpp>
#include <sfge/behaviours/render_behaviour.hpp>
#include <sfge/behaviours/input_behaviour.hpp>

using namespace std;
using namespace sfge;

class ControllerBehaviour : public InputBehaviour
{
public:
	ControllerBehaviour(GameObjectPtr owner)
		: InputBehaviour(owner), mMouseX(0), mMouseY(0)
	{
	}

	virtual void OnUpdate(float /*dt*/)
	{
		unsigned int	newX	= mInput.GetMouseX(),
						newY	= mInput.GetMouseY();
		const bool mouseMoved	= newX != mMouseX || newY != mMouseY;

		if (newX != mMouseX)
			mMouseX = newX;

		if (newY != mMouseY)
			mMouseY = newY;

		if (mouseMoved)
			cout << "{" << mMouseX << ", " << mMouseY << "}" << endl;

		Attribute<sf::Vector2f> pos = GetAttribute<sf::Vector2f>(AK_GO_POSITION);
	}

private:
	unsigned int mMouseX, mMouseY;
};

class SampleGame : public Game
{
public:
	SampleGame()	{ ; }

protected:
	virtual void OnEndSystemInit()
	{
		GraphicSystem::getSingleton().Create(GraphicSystem::InitParams());

		GameObjectPtr go = GameObject::Create();
		go->AddBehaviour(BehaviourPtr(new RenderBehaviour(go)));
		go->AddBehaviour(BehaviourPtr(new ControllerBehaviour(go)));
		mObjects.push_back(go);
	}
};

int main(int argc, char **argv)
{
	SampleGame g;
	g.Run();

	return 0;
}
