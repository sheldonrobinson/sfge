#include <sfge/infrastructure/behaviour.hpp>
#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/data_store.hpp>
#include <sfge/infrastructure/game.hpp>
#include <sfge/infrastructure/game_object.hpp>
#include <sfge/infrastructure/message_manager.hpp>
#include <sfge/graphics/graphic_system.hpp>

#include <iostream>

#include <boost/lexical_cast.hpp>

#include <SFML/Graphics/Shape.hpp>

using namespace std;
using namespace boost;
using namespace sf;
using namespace sfge;

class ControllerBehaviour : public Behaviour
{
public:
	ControllerBehaviour(GameObjectPtr owner = GameObjectPtr())
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
	OrbiterBehaviour(GameObjectPtr owner = GameObjectPtr())
		: Behaviour(owner)
	{
	}
	
	virtual void OnParamsReceived(const Parameters &params) override
	{
		mDistanceFrom	= params.get("distance", 0.f);
		mSpeed			= params.get("speed", 0.f);

		const std::string &refObjName = params.get("revCenter", "");
		mRefObj = DataStore::getSingleton().GetGameObjectInstanceByName(refObjName);
	}

	virtual void OnUpdate(float dt) override
	{
		Vector2f orbitCenter(400, 300);
		if (mRefObj)
		{
			const Attribute<Vector2f> refPos = mRefObj->GetAttribute<Vector2f>(AK_Position);
			assert(refPos.IsValid());
			orbitCenter = refPos;
		}

		dt *= mSpeed;

		Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
		assert(pos.IsValid());

		pos->x = cos(dt) * mDistanceFrom + orbitCenter.x;
		pos->y = sin(dt) * mDistanceFrom + orbitCenter.y;
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
	virtual void OnDeclareAdditionnalBehaviours() override
	{
		DECLARE_BEHAVIOUR(ControllerBehaviour);
		DECLARE_BEHAVIOUR(OrbiterBehaviour);
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

		Parameters orbitObjDrawableDef;
		orbitObjDrawableDef.put("type",		"shape");
		orbitObjDrawableDef.put("shape",	"circle");
		orbitObjDrawableDef.put("cx",		0);
		orbitObjDrawableDef.put("cy",		0);
		orbitObjDrawableDef.put("radius",	15);
		orbitObjDrawableDef.put("cr",		Color::White.r);
		orbitObjDrawableDef.put("cg",		Color::White.g);
		orbitObjDrawableDef.put("cb",		Color::White.b);
		orbitObjDrawableDef.put("ca",		Color::White.a);
		
		Parameters orbitParams;
		orbitParams.put("distance",		100.f);
		orbitParams.put("speed",		5.f);
		orbitParams.put("revCenter",	"refObj");

		// Declare the 2 gameobject definitions we need
		DataStore &ds = DataStore::getSingleton();

		ds.DeclareGameObjectDef("ControllableThing");
		ds.DeclareGameObjectDef("OrbitingThing");

		// Create the links between gameobject definitions and registered behaviours (eventually settings some default params)
		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "TransformBehaviour");
		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "ControllerBehaviour");
		ds.LinkBehaviourDefToGameObjectDef("ControllableThing", "RenderBehaviour",	refObjDrawableDef);
		
		ds.LinkBehaviourDefToGameObjectDef("OrbitingThing", "TransformBehaviour");
		ds.LinkBehaviourDefToGameObjectDef("OrbitingThing", "OrbiterBehaviour",		orbitParams);
		ds.LinkBehaviourDefToGameObjectDef("OrbitingThing", "RenderBehaviour",		orbitObjDrawableDef);
	}

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
