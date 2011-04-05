#ifndef SFGE_UTILITIES_PTREE_PARSE_HELPERS_HPP
#define SFGE_UTILITIES_PTREE_PARSE_HELPERS_HPP

#include <boost/property_tree/ptree.hpp>

namespace sfge
{
	template <typename T>
	void parseTo(const boost::property_tree::ptree &ptree, T &out)
	{
		static_assert(0, "No parser available for the requested type.");
	}
}

#endif