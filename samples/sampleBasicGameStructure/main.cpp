#include <iostream>

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/game.hpp>
#include <sfge/infrastructure/game_object.hpp>
#include <sfge/graphics/graphic_system.hpp>
#include <sfge/behaviours/render_behaviour.hpp>
#include <sfge/behaviours/input_behaviour.hpp>

#include <SFML/Graphics/Shape.hpp>

using namespace std;
using namespace sf;
using namespace sfge;

class ControllerBehaviour : public InputBehaviour
{
public:
	ControllerBehaviour(GameObjectPtr owner)
		: InputBehaviour(owner)
	{
	}

	virtual void OnUpdate(float /*dt*/)
	{
		unsigned int	newX	= mInput.GetMouseX(),
						newY	= mInput.GetMouseY();
		bool mouseLeftPressed	= mInput.IsMouseButtonDown(sf::Mouse::Left);

		Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_GO_POSITION);
		assert(pos.IsValid());
		pos->x = static_cast<float>(newX);
		pos->y = static_cast<float>(newY);

		Attribute<Color> col = GetAttribute<Color>(AK_RB_COLOR);
		assert(col.IsValid());
		col = mouseLeftPressed ? Color::Blue : Color::Red;
	}
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
		go->AddBehaviour(BehaviourPtr(new RenderBehaviour(go, DrawablePtr(new sf::Shape(sf::Shape::Circle(0, 0, 50, sf::Color::Magenta))))));
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
