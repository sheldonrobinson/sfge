#include "sfge/infrastructure/message_manager.hpp"
#include "sfge/infrastructure/game_object.hpp"

#include <algorithm>

using namespace std;

namespace sfge
{

MessageManager*	MessageManager::ms_Singleton = 0;

void MessageManager::Init()
{
	new MessageManager();
}

MessageManager::MessageManager()
{
}

void MessageManager::SubscribeTo(const MessageKey &msgKey, const MessageReceiver &msgReceiver)
{
	mSubscriptions.insert(make_pair(msgKey, msgReceiver));
}

void MessageManager::Queue(const Message &msg)
{
	// TODO THREADING check thread hosting the receiver; if different than the sender, copy it to the targeted thread's message queue.
	MessageKey key(msg);
	
	pair<MessageSubscriptions::const_iterator, MessageSubscriptions::const_iterator> slots = mSubscriptions.equal_range(key);
	for_each(slots.first, slots.second, [&] (const MessageSubscriptions::value_type &slot) { slot.second(msg); } );
}

}