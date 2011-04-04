#include "sfge/behaviours/transform_behaviour.hpp"

#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/message_manager.hpp"

using namespace boost;
using namespace sf;

namespace sfge
{

TransformBehaviour::TransformBehaviour(GameObjectWeakPtr owner)
	: Behaviour(owner)
{
	RegisterAttribute<Vector2f>(AK_Position);
	RegisterAttribute<Vector2f>(AK_Scale, Vector2f(1, 1));
	RegisterAttribute<GraphicSystem::LayerIndex>(AK_LayerIndex, (GraphicSystem::LayerIndex)0);
}

void TransformBehaviour::OnParamsReceived(const sfge::Parameters &params)
{
	// Apply position if found
	optional<float> px = params.get_optional<float>("px");
	optional<float> py = params.get_optional<float>("py");

	Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
	if (px)
		pos->x = *px;
	if (py)
		pos->y = *py;
	
	optional<float> sx = params.get_optional<float>("sx");
	optional<float> sy = params.get_optional<float>("sy");
	
	// Apply scale if found
	Attribute<Vector2f> scale = GetAttribute<Vector2f>(AK_Scale);
	if (sx)
		scale->x = *sx;
	if (sy)
		scale->y = *sy;

	// Apply layer if found
	optional<GraphicSystem::LayerIndex> layer = params.get_optional<GraphicSystem::LayerIndex>("layer");
	if (layer)
		GetAttribute<GraphicSystem::LayerIndex>(AK_LayerIndex) = *layer;
}

}
