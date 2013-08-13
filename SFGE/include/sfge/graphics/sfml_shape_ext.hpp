#ifndef SFGE_GRAPHICS_SFML_SHAPE_EXT_HPP
#define SFGE_GRAPHICS_SFML_SHAPE_EXT_HPP

#include "sfge/graphics/sfml_drawable_ext.hpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "sfge/math/circle.hpp"

namespace sfge
{
	template <typename VectorStorageT>
	ShapePtr shapeFromCircle(const Circle<VectorStorageT> &circle, const sf::Color &c);

#include "sfml_shape_ext.inl"
}

#endif
