#ifndef SFGE_GRAPHICS_SFML_TYPES_HPP
#define SFGE_GRAPHICS_SFML_TYPES_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Shape.hpp>

namespace sfge
{
	typedef std::shared_ptr<sf::Shape>	ShapePtr;
	typedef std::vector<ShapePtr>		Shapes;
}

#endif
