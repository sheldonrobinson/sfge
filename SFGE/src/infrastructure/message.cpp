#include "sfge/infrastructure/message.hpp"

#include <boost/functional/hash.hpp>

namespace sfge
{

size_t MessageKey::hash_value(const MessageKey &k) const
{
	size_t seed = 0;
	boost::hash_combine(seed, k.mSource.lock().get());
	boost::hash_combine(seed, k.mID);
	return seed;
}

}
