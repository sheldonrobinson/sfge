#include "sfge/behaviours/transform_behaviour.hpp"

#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/message_manager.hpp"
#include "sfge/utilities/ptree_parse_helpers_sfml.hpp"

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
	// Empty Parameters used as default return value
	const Parameters defParams;

	// Apply position if found
	const Parameters &pos = params.get_child("position", defParams);
	if (pos.size() > 0)
		parseTo(pos, *GetAttribute<Vector2f>(AK_Position));
	
	// Apply scale if found
	const Parameters &scale = params.get_child("scale", defParams);
	if (scale.size() > 0)
		parseTo(scale, *GetAttribute<Vector2f>(AK_Scale));

	// Apply layer if found
	optional<GraphicSystem::LayerIndex> layer = params.get_optional<GraphicSystem::LayerIndex>("layer");
	if (layer)
		GetAttribute<GraphicSystem::LayerIndex>(AK_LayerIndex) = *layer;
}

}
