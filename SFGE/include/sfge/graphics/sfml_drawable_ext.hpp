#ifndef SFGE_GRAPHICS_SFML_DRAWABLE_EXT_HPP
#define SFGE_GRAPHICS_SFML_DRAWABLE_EXT_HPP

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Shader.hpp>

namespace sfge
{
	typedef std::shared_ptr<sf::Drawable>	DrawablePtr;
	typedef std::shared_ptr<sf::Shape>		ShapePtr;
	typedef std::shared_ptr<sf::Sprite>		SpritePtr;
	typedef std::shared_ptr<sf::Image>		ImagePtr;
	typedef std::shared_ptr<sf::Shader>		ShaderPtr;
}

#endif
