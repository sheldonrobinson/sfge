#ifndef SFGE_UTILITIES_NULL_DELETER_HPP
#define SFGE_UTILITIES_NULL_DELETER_HPP

namespace sfge
{
	struct null_deleter
	{
		void operator()(void const *) const
		{
		}
	};
}

#endif
