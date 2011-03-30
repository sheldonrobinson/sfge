#ifndef SFGE_GRAPHICS_LIGHT_HPP
#define SFGE_GRAPHICS_LIGHT_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "sfge/graphics/sfml_shape_ext.hpp"
#include "sfge/math/circle.hpp"
#include "sfge/math/edge.hpp"

namespace sfge
{
	class Light
	{
	public:
		Light();
		Light(const sf::Vector2f &pos, float rad);

		void addOccluders(const Shapes &occluders);

		void reset();

		void setPosition(sf::Vector2f &pos)			{ mLightDesc.mPos = pos; }
		void setRadius(float radius)				{ mLightDesc.mRadius = radius; }

		sf::Vector2f&	getPosition()				{ return mLightDesc.mPos; }
		float&			getRadius()					{ return mLightDesc.mRadius; }

		const sf::Vector2f&	getPosition() const		{ return mLightDesc.mPos; }
		float				getRadius()	const		{ return mLightDesc.mRadius; }

		void DrawShadows(sf::RenderTarget &target) const;
		void DebugDraw(sf::RenderTarget &target) const;

		sf::Color		mShadowOutline;
		sf::Color		mShadowFill;

	private:
		/* Return false if occluder hasn't been added because of distance
		 * or if light has been detected to be within an occluder.
		 * NB: the function may return true if the occluder hasn't been
		 * used for *other* reasons.
		 */
		bool addOccluder(const sf::Shape &occluder);

		//! Generate the shadow from what has been defined as the occluding line for an occluder.
		void generateShadowFromLine(Edge2f &e);

	private:
		typedef Shapes	Shadows;

	private:
		Circle<float>	mLightDesc;

		Shadows			mShadows;
		bool			mIsInside;
	};
}

#endif
