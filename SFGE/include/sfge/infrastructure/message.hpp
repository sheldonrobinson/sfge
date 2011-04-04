#ifndef SFGE_INFRASTRUCTURE_MESSAGE_HPP
#define SFGE_INFRASTRUCTURE_MESSAGE_HPP

#include "sfge/infrastructure/infrastructure_fwd.hpp"
#include "sfge/utilities/delegate.hpp"
#include "sfge/infrastructure/detail/value_holder.hpp"

namespace sfge
{
	const size_t InvalidMessageID = ~0;

	struct Message
	{
		Message() : mID(InvalidMessageID) { ; }

		GameObjectWeakPtr		mSource;
		size_t					mID;
		detail::ValueHolder		mData;
	};

	struct MessageKey
	{
		MessageKey () : mID(InvalidMessageID)								{ ; }

		//! This will be used to create the message in the messages list handled by the manager (in case the key doesn't yet exist)
		MessageKey(const Message &m) : mSource(m.mSource), mID(m.mID)		{ ; }

		bool operator<(const MessageKey &other) const
		{
			return hash_value(*this) < hash_value(other);
		}

		size_t hash_value(const MessageKey &k) const;

		GameObjectWeakPtr	mSource;
		size_t				mID;
	};

	typedef delegate<void(const Message &msg)>	MessageReceiver;
}

#endif
