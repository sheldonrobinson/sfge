#ifndef SFGE_GRAPHICS_LIGHT_HPP
#define SFGE_GRAPHICS_LIGHT_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "sfge/graphics/sfml_types.hpp"
#include "sfge/math/edge.hpp"

namespace sfge
{
	class Light
	{
	public:
		Light();
		Light(const sf::Vector2f &pos, float rad);

		void DebugDraw(sf::RenderTarget &target) const;

		void reset();

		void addOccluders(const Shapes &occluders);

		/* Return false if occluder hasn't been added because of distance
		 * or if light has been detected to be within an occluder.
		 * NB: the function may return true if the occluder hasn't been
		 * used for *other* reasons.
		 */
		bool addOccluder(const sf::Shape &occluder);

		void DrawShadows(sf::RenderTarget &target) const;

		sf::Vector2f	mPos;
		float			mRadius;

		sf::Color		mShadowOutline;
		sf::Color		mShadowFill;

	private:
		void generateShadowFromLine(Edge2f &e);

	private:
		typedef Shapes	Shadows;

	private:
		Shadows		mShadows;
		bool		mIsInside;
	};
}

#endif
