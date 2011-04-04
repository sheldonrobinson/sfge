#ifndef SFGE_UTILITIES_BOOST_PROPTREE_TYPES_HPP
#define SFGE_UTILITIES_BOOST_PROPTREE_TYPES_HPP

#include <memory>
#include <boost/property_tree/ptree.hpp>

namespace sfge
{
	typedef boost::property_tree::ptree			Parameters;
	typedef std::shared_ptr<const Parameters>	ParametersConstPtr;
	typedef std::shared_ptr<Parameters>			ParametersPtr;
}

#endif
