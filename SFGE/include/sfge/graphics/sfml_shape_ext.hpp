#ifndef SFGE_GRAPHICS_SFML_SHAPE_EXT_HPP
#define SFGE_GRAPHICS_SFML_SHAPE_EXT_HPP

#include <memory>
#include <vector>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>

#include "sfge/math/circle.hpp"

namespace sfge
{
	typedef std::shared_ptr<sf::Shape>	ShapePtr;
	typedef std::vector<ShapePtr>		Shapes;

	template <typename VectorStorageT>
	sf::Shape shapeFromCircle(const Circle<VectorStorageT> &circle, const sf::Color &c);

#include "sfml_shape_ext.inl"
}

#endif
