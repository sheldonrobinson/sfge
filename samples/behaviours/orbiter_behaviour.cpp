#include "orbiter_behaviour.hpp"
#include "sampleAttributes.hpp"

#include <sfge/infrastructure/builtin_attributes.hpp>
#include <sfge/infrastructure/data_store.hpp>

using namespace boost;
using namespace std;
using namespace sfge;
using namespace sf;

OrbiterBehaviour::OrbiterBehaviour(GameObjectPtr owner)
	: Behaviour(owner)
{
	RegisterAttribute(SAK_OrbitDistance, 0.f);
	RegisterAttribute(SAK_OrbitSpeed, 0.f);
	RegisterAttribute<GameObjectPtr>(SAK_OrbitReferenceCenter);
}
	
void OrbiterBehaviour::OnParamsReceived(const sfge::Parameters &params)
{
	optional<float> dist = params.get_optional<float>("distance");
	if (dist)
		GetAttribute<float>(SAK_OrbitDistance) = *dist;

	optional<float> speed = params.get_optional<float>("speed");
	if (dist)
		GetAttribute<float>(SAK_OrbitSpeed) = *speed;

	optional<string> refObjName = params.get_optional<string>("revolutionCenter");
	if (refObjName)
		GetAttribute<GameObjectPtr>(SAK_OrbitReferenceCenter) = DataStore::getSingleton().GetGameObjectInstanceByName(*refObjName);
}

void OrbiterBehaviour::OnUpdate(float dt)
{
	const float dist			= GetAttribute<float>(SAK_OrbitDistance);
	const float speed			= GetAttribute<float>(SAK_OrbitSpeed);
	const GameObjectPtr refObj	= GetAttribute<GameObjectPtr>(SAK_OrbitReferenceCenter);
	
	const Attribute<Vector2f> refPos = refObj->GetAttribute<Vector2f>(AK_Position);
	assert(refPos.IsValid());

	Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
	assert(pos.IsValid());

	const float theta = dt * speed;

	pos->x = cos(theta) * dist + refPos->x;
	pos->y = sin(theta) * dist + refPos->y;
}
