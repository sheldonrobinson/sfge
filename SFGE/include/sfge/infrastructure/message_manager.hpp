#ifndef SFGE_INFRASTRUCTURE_MESSAGE_MANAGER_HPP
#define SFGE_INFRASTRUCTURE_MESSAGE_MANAGER_HPP

#include <map>
#include <queue>
#include <set>

#include <boost/functional/hash.hpp>

#include "sfge/infrastructure/infrastructure_fwd.hpp"

#include "sfge/utilities/delegate.hpp"
#include "sfge/utilities/singleton.hpp"

namespace sfge
{
	const size_t InvalidMessageID = ~0;

	struct Message
	{
		Message() : mMessageID(InvalidMessageID), mMsgData(0) { ; }

		GameObjectWeakPtr	mSource;
		size_t			mMessageID;
		size_t			mMsgData;
	};

	struct MessageKey
	{
		MessageKey () : mMessageID(InvalidMessageID)									{ ; }

		//! This will be used to create the message in the messages list handled by the manager (in case the key doesn't yet exist)
		MessageKey(const Message &m) : mSource(m.mSource), mMessageID(m.mMessageID)		{ ; }

		bool operator<(const MessageKey &other) const
		{
			return hash_value(*this) < hash_value(other);
		}

		friend size_t hash_value(const MessageKey &k)
		{
			size_t seed = 0;
			boost::hash_combine(seed, k.mSource.lock().get());
			boost::hash_combine(seed, k.mMessageID);
			return seed;
		}

		GameObjectWeakPtr	mSource;
		size_t			mMessageID;
	};
	
	typedef delegate<void(const Message &msg)>	MessageReceiver;

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
