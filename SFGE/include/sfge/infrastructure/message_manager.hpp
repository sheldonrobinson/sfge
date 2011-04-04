#ifndef SFGE_INFRASTRUCTURE_MESSAGE_MANAGER_HPP
#define SFGE_INFRASTRUCTURE_MESSAGE_MANAGER_HPP

#include <map>
// TODO THREADING
//#include <queue>
#include <set>

#include "sfge/infrastructure/message.hpp"
#include "sfge/utilities/singleton.hpp"

namespace sfge
{

	// TODO THREADING get rid of this singleton
	class MessageManager : public Singleton<MessageManager>
	{
	public:
		static void Init();

	public:
		void SubscribeTo(const MessageKey &msgKey, const MessageReceiver &msgReceiver);
		void Queue(const Message &msg);

	private:
		MessageManager();

	private:
		typedef std::set<MessageReceiver>				ReceiverContainer;
		typedef std::map<MessageKey, ReceiverContainer>	MessageSubscriptions;
		// TODO THREADING
		//typedef std::queue<Message>						MessageQueue;

	private:
		MessageSubscriptions	mSubscriptions;
		// TODO THREADING
		//MessageQueue			mMessageQueue;
	};
}

#endif
