#include "orbiter_behaviour.hpp"

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/data_store.hpp>

using namespace sfge;
using namespace sf;

OrbiterBehaviour::OrbiterBehaviour(GameObjectPtr owner)
	: Behaviour(owner)
{
}
	
void OrbiterBehaviour::OnParamsReceived(const sfge::Parameters &params)
{
	mDistanceFrom	= params.get("distance", 0.f);
	mSpeed			= params.get("speed", 0.f);

	const std::string &refObjName = params.get("revolutionCenter", "");
	mRefObj = DataStore::getSingleton().GetGameObjectInstanceByName(refObjName);
}

void OrbiterBehaviour::OnUpdate(float dt)
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
