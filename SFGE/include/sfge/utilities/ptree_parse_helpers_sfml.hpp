#ifndef SFGE_UTILITIES_PTREE_PARSE_HELPERS_SFML_HPP
#define SFGE_UTILITIES_PTREE_PARSE_HELPERS_SFML_HPP

#include "sfge/utilities/ptree_parse_helpers.hpp"

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Color.hpp>

namespace sfge
{
	template <>
	void parseTo<sf::Vector2f>(const boost::property_tree::ptree &ptree, sf::Vector2f &out);

	template <>
	void parseTo<sf::IntRect>(const boost::property_tree::ptree &ptree, sf::IntRect &out);

	template <>
	void parseTo<sf::Color>(const boost::property_tree::ptree &ptree, sf::Color &out);
}

#endif