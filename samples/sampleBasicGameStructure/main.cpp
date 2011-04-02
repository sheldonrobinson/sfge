#include <iostream>

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/data_store.hpp>
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
	ControllerBehaviour(GameObjectPtr owner, const Parameters &params)
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
	OrbiterBehaviour(GameObjectPtr owner, const Parameters &params)
		: Behaviour(owner), mDistanceFrom(0), mSpeed(0)
	{
	}

	virtual void OnUpdate(float dt) override
	{
		if (!mRefObj)
			return;

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

		// Setup data store
		DataStore &ds = DataStore::getSingleton();
		ds.DeclareGameObjectDef("ControllableThing");
		ds.DeclareGameObjectDef("OrbitingThing");

		DECLARE_BEHAVIOUR(ds, TransformBehaviour);
		DECLARE_BEHAVIOUR(ds, ControllerBehaviour);
		DECLARE_BEHAVIOUR(ds, OrbiterBehaviour);

		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "TransformBehaviour");
		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "ControllerBehaviour");
		
		ds.LinkBehaviourDefToGameObjectDef("OrbitingThing", "TransformBehaviour");
		Parameters orbitParams;
		orbitParams.push_back(make_pair("distance",		"100"));
		orbitParams.push_back(make_pair("speed",		"5"));
		orbitParams.push_back(make_pair("revCenter",	"refObj"));
		ds.LinkBehaviourDefToGameObjectDef("OrbitingThing", "OrbiterBehaviour", orbitParams);

		// Setup scene
		GameObjectPtr refGO = ds.InstantiateGameObjectDef("ControllableThing");
		refGO->AddBehaviour(BehaviourPtr(new RenderBehaviour(refGO, Parameters(), DrawablePtr(new sf::Shape(sf::Shape::Circle(0, 0, 50, sf::Color::Magenta))))));
		mObjects.push_back(refGO);

		GameObjectPtr orbiterGO = ds.InstantiateGameObjectDef("OrbitingThing");
		orbiterGO->AddBehaviour(BehaviourPtr(new RenderBehaviour(orbiterGO, Parameters(), DrawablePtr(new sf::Shape(sf::Shape::Circle(0, 0, 15, sf::Color::White))))));
		mObjects.push_back(orbiterGO);
	}
};

int main(int argc, char **argv)
{
	SampleGame g;
	g.Run();

	return 0;
}
