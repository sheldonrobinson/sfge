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
	mSubscriptions[msgKey].insert(msgReceiver);
}

void MessageManager::Queue(const Message &msg)
{
	// TODO THREADING check thread hosting the receiver; if different than the sender, copy it to the targeted thread's message queue.
	MessageKey key(msg);
	
	const MessageSubscriptions::const_iterator msgKeyIt = mSubscriptions.find(key);
	if (msgKeyIt == mSubscriptions.end())
		return;

	const ReceiverContainer &slots = msgKeyIt->second;
	for_each(slots.begin(), slots.end(), [&] (const MessageReceiver &slot) { slot(msg); } );
}

}