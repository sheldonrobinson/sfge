#include "sfge/utilities/ptree_parse_helpers_sfml.hpp"
#include "sfge/utilities/exception_str.hpp"

using namespace sf;
using namespace boost::property_tree;

namespace sfge
{

template <>
void sfge::parseTo<Vector2f>(const ptree &ptree, Vector2f &out)
{
	if (ptree.size() != 2)
		throw ExceptionStr("Malformed Vector2 in description: 2 values required.");

	ptree::const_assoc_iterator it = ptree.ordered_begin();
	
	out.x	= it->second.get_value<float>();	++it;
	out.y	= it->second.get_value<float>();
}

template <>
void sfge::parseTo<IntRect>(const ptree &ptree, IntRect &out)
{
	if (ptree.size() != 4)
		throw ExceptionStr("Malformed Rect in description: 4 values required.");

	ptree::const_assoc_iterator it = ptree.ordered_begin();
	
	out.left	= it->second.get_value<int>();		++it;
	out.top		= it->second.get_value<int>();		++it;
	out.width	= it->second.get_value<int>();		++it;
	out.height	= it->second.get_value<int>();
}

template <>
void sfge::parseTo<Color>(const ptree &ptree, Color &out)
{
	if (ptree.size() != 3 && ptree.size() != 4)
		throw ExceptionStr("Malformed Color in description: 3 or 4 values required.");

	ptree::const_assoc_iterator it = ptree.ordered_begin();
	
	out.r	= it->second.get_value<Uint8>();	++it;
	out.g	= it->second.get_value<Uint8>();	++it;
	out.b	= it->second.get_value<Uint8>();	++it;
	if (it != ptree.not_found())
		out.a	= it->second.get_value<Uint8>();
}

}
