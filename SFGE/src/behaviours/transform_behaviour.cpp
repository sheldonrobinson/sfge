#include "sfge/behaviours/transform_behaviour.hpp"
#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/game_object.hpp"

using namespace boost;
using namespace sf;

namespace sfge
{

TransformBehaviour::TransformBehaviour(GameObjectPtr owner)
	: Behaviour(owner)
{
	RegisterAttribute<Vector2f>(AK_Position);
}

void TransformBehaviour::OnParamsReceived(const sfge::Parameters &params)
{
	optional<float> x = params.get_optional<float>("px");
	optional<float> y = params.get_optional<float>("py");

	Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
	if (x)
		pos->x = *x;
	if (y)
		pos->y = *y;
}

}
