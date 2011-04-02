#include <iostream>

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/game.hpp>
#include <sfge/infrastructure/game_object.hpp>
#include <sfge/infrastructure/message_manager.hpp>
#include <sfge/graphics/graphic_system.hpp>
#include <sfge/behaviours/render_behaviour.hpp>
#include <sfge/behaviours/transform_behaviour.hpp>

#include <SFML/Graphics/Shape.hpp>

using namespace std;
using namespace sf;
using namespace sfge;

class ControllerBehaviour : public Behaviour
{
public:
	ControllerBehaviour(GameObjectPtr owner)
		: Behaviour(owner), mPrevMouseX(0), mPrevMouseY(0), mPrevLButtonState(false)
	{
	}

	virtual void OnUpdate(float /*dt*/) override
	{
		const sf::Input	&input(GraphicSystem::getSingleton().GetInput());

		const unsigned int	newX	= input.GetMouseX(),
							newY	= input.GetMouseY();

		if (newX != mPrevMouseX || newY != mPrevMouseY)
		{
			Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
			assert(pos.IsValid());
			pos->x = static_cast<float>(newX);
			pos->y = static_cast<float>(newY);

			mPrevMouseX = newX;
			mPrevMouseY = newY;
		}

		const bool mouseLeftPressed	= input.IsMouseButtonDown(sf::Mouse::Left);
		if (mouseLeftPressed != mPrevLButtonState)
		{
			Attribute<Color> col = GetAttribute<Color>(AK_Color);
			assert(col.IsValid());
			col = mouseLeftPressed ? Color::Blue : Color::Red;

			mPrevLButtonState = mouseLeftPressed;
		}
	}

private:
	unsigned int	mPrevMouseX, mPrevMouseY;
	bool			mPrevLButtonState;
};

class OrbiterBehaviour : public Behaviour
{
public:
	OrbiterBehaviour(GameObjectPtr owner)
		: Behaviour(owner)
	{
	}

	virtual void OnUpdate(float dt) override
	{
		dt *= mSpeed;

		const Attribute<Vector2f> refPos = mRefObj->GetAttribute<Vector2f>(AK_Position);
		assert(refPos.IsValid());

		Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
		assert(pos.IsValid());

		pos->x = cos(dt) * mDistanceFrom + refPos->x;
		pos->y = sin(dt) * mDistanceFrom + refPos->y;
	}

	void	SetOrbitInfo(float dist, float speed, const GameObjectPtr &refObj)
	{
		mDistanceFrom	= dist;
		mSpeed			= speed;
		mRefObj			= refObj;
	}

private:
	float			mDistanceFrom;
	float			mSpeed;
	GameObjectPtr	mRefObj;
};

class SampleGame : public Game
{
public:
	SampleGame()	{ ; }

protected:
	virtual void OnEndSystemInit() override
	{
		GraphicSystem::getSingleton().Create(GraphicSystem::InitParams());

		GameObjectPtr refGO = GameObject::Create();
		refGO->AddBehaviour(BehaviourPtr(new RenderBehaviour(refGO, DrawablePtr(new sf::Shape(sf::Shape::Circle(0, 0, 50, sf::Color::Magenta))))));
		refGO->AddBehaviour(BehaviourPtr(new TransformBehaviour(refGO)));
		refGO->AddBehaviour(BehaviourPtr(new ControllerBehaviour(refGO)));
		mObjects.push_back(refGO);

		GameObjectPtr orbiterGO = GameObject::Create();
		orbiterGO->AddBehaviour(BehaviourPtr(new RenderBehaviour(orbiterGO, DrawablePtr(new sf::Shape(sf::Shape::Circle(0, 0, 15, sf::Color::White))))));
		orbiterGO->AddBehaviour(BehaviourPtr(new TransformBehaviour(orbiterGO)));
		OrbiterBehaviour *orbiter(new OrbiterBehaviour(orbiterGO));
		orbiter->SetOrbitInfo(100, 5, refGO);
		orbiterGO->AddBehaviour(BehaviourPtr(orbiter));
		mObjects.push_back(orbiterGO);
	}
};

int main(int argc, char **argv)
{
	SampleGame g;
	g.Run();

	return 0;
}
