#include "sfge/behaviours/camera_behaviour.hpp"

#include "sfge/infrastructure/attribute.hpp"
#include "sfge/infrastructure/builtin_attributes.hpp"
#include "sfge/infrastructure/game_object.hpp"
#include "sfge/infrastructure/message_manager.hpp"
#include "sfge/graphics/graphic_system.hpp"

#include <SFML/Graphics/View.hpp>

using namespace boost;
using namespace sf;

namespace sfge
{

CameraBehaviour::CameraBehaviour(GameObjectWeakPtr owner)
	: Behaviour(owner)
{
	MessageKey msgKey;
	msgKey.mID		= MID_AttributeChanged;
	msgKey.mSource	= mOwner;
	MessageReceiver slot = MessageReceiver::from_method<CameraBehaviour, &CameraBehaviour::OnAttributeChanged>(this);
	MessageManager::getSingleton().SubscribeTo(msgKey, slot);
}

void CameraBehaviour::OnParamsReceived(const sfge::Parameters &params)
{
}

void CameraBehaviour::OnAttributeChanged(const Message &msg)
{
	assert(msg.mSource.lock().get() == mOwner.lock().get());

	
	switch (msg.mData.GetValue<AttributeKey>())
	{
	case AK_Position:
		{
			const Attribute<Vector2f> pos = GetAttribute<Vector2f>(AK_Position);
			assert(pos.IsValid());
			
			View view = GraphicSystem::getSingleton().GetCurrentRenderTarget().getView();
			view.setCenter(pos);
			GraphicSystem::getSingleton().GetCurrentRenderTarget().setView(view);
		}
		break;

	case AK_Scale:
		{
			const Attribute<Vector2f> scale = GetAttribute<Vector2f>(AK_Scale);
			assert(scale.IsValid());
			
			View view = GraphicSystem::getSingleton().GetCurrentRenderTarget().getView();
			const Vector2f &currSize = view.getSize();
			view.setSize(currSize.x * scale->x, currSize.y * scale->y);
			GraphicSystem::getSingleton().GetCurrentRenderTarget().setView(view);
		}
		break;
	}
	
}

}
