#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>

#include <boost/array.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <sfge/graphics/sfml_shape_ext.hpp>
#include <sfge/graphics/light.hpp>

namespace DemoSettings
{
	static const bool	EnableFrameRateLimit	= false;
	static const int	FrameRateLimit			= 60;

	static const bool	UseBigBugOccluder		= false;
	static const bool	UseSpheresAsOccluders	= true;
	static const int	OccludersCount			= 125;
	static const float	OccludersRange			= 275;

	static const float	DefaultLightsRadius		= 250;
	static const int	WheelFactorToLightRad	= 5;

	static const bool	EnableManualLight		= false;
	static const bool	EnableOnlyManualLight	= false;

	// Live tweaking vars
	static bool	DrawOccluders			= true;
	static bool	EnableLightsDebugDraw	= false;
	static bool	EnableShadowsOutline	= false;
}

using namespace std;
using namespace boost;
using namespace sf;
using namespace sfge;

struct null_deleter
{
    void operator()(void const *) const
    {
    }
};

typedef std::shared_ptr<Light> LightPtr;

bool handleEvents(Window &wnd, LightPtr light)
{
	Event evt;
	while (wnd.pollEvent(evt))
	{
		switch(evt.type)
		{
		case Event::Closed:
			return true;
			break;

		case Event::KeyPressed:
			switch(evt.key.code)
			{
			case Keyboard::Escape:
				return true;
				break;

			case Keyboard::F1:
				DemoSettings::DrawOccluders = !DemoSettings::DrawOccluders;
				break;

			case Keyboard::F2:
				DemoSettings::EnableLightsDebugDraw = !DemoSettings::EnableLightsDebugDraw;
				break;

			case Keyboard::F3:
				DemoSettings::EnableShadowsOutline = !DemoSettings::EnableShadowsOutline;
				break;
			}
			break;

		case Event::MouseMoved:
			if (DemoSettings::EnableManualLight || DemoSettings::EnableOnlyManualLight)
				light->setPosition(Vector2f(static_cast<float>(evt.mouseMove.x),
									        static_cast<float>(evt.mouseMove.y)));
			break;

		case Event::MouseWheelMoved:
			if (DemoSettings::EnableManualLight || DemoSettings::EnableOnlyManualLight)
				light->getRadius() += evt.mouseWheel.delta * DemoSettings::WheelFactorToLightRad;
			break;
		}
	}

	return false;
}

int main(int argc, char **argv)
{
	RenderWindow wnd(VideoMode(800, 600), "Test dynamic lights");
	if (DemoSettings::EnableFrameRateLimit)
		wnd.setFramerateLimit(DemoSettings::FrameRateLimit);
	wnd.setVisible(true);

	Texture bgTexture;
	bgTexture.loadFromFile("data/grass.png");
	Sprite bgSpr(bgTexture);

#pragma region Generate some occluders
	Shapes occluders(DemoSettings::OccludersCount);
	const Vector2f center(400, 300);
	const float r = DemoSettings::OccludersRange;
	const float td = 3.141592f * 2 / occluders.size();
	float t = 0.f;
	auto getNextOccPos = [&] () -> Vector2f { Vector2f p(cos(t) * r, sin(t) * r); t += td; return p + center; };
	if (DemoSettings::UseBigBugOccluder)
	{
        std::shared_ptr<sf::RectangleShape> s(new sf::RectangleShape(sf::Vector2f(250.0f, 50.0f)));
        s->setPosition(400.0f, 300.0f);
        s->setFillColor(Color::Cyan);
		occluders[0] = s;
		occluders.resize(1);
	}
	else if (DemoSettings::UseSpheresAsOccluders)
	{
		generate(occluders.begin(), occluders.end(),
			[&] () -> ShapePtr
			{
                std::shared_ptr<sf::CircleShape> s(new sf::CircleShape(6.0f));
                s->setFillColor(Color::Cyan);
				s->setPosition(getNextOccPos());
				return s;
			} );
	}
	else
	{
		generate(occluders.begin(), occluders.end(),
			[&] () -> ShapePtr
			{
                std::shared_ptr<sf::RectangleShape> s(new sf::RectangleShape(sf::Vector2f(6.0f, 6.0f)));
                s->setFillColor(Color::Cyan);
				s->setPosition(getNextOccPos());
				return s;
			} );
	}
#pragma endregion

#pragma region Generate lights
	vector<LightPtr> lights;

	if (!DemoSettings::EnableOnlyManualLight)
	{
		generate_n(back_inserter(lights), 4,
			[&] () -> LightPtr
			{ return LightPtr(new Light(center, DemoSettings::DefaultLightsRadius)); } );
	}
	
	if (DemoSettings::EnableManualLight || DemoSettings::EnableOnlyManualLight)
		lights.push_back(LightPtr(new Light(center, DemoSettings::DefaultLightsRadius)));
	const float autoLightsRadius = DemoSettings::OccludersRange - DemoSettings::DefaultLightsRadius * 0.5f;
#pragma endregion

	RenderTexture shadowMap;
	shadowMap.create(800, 600);
	Sprite shadowMapSprite;

	sf::Clock timer;
	sf::Clock clock;
	while (wnd.isOpen())
	{
		if (handleEvents(wnd, *lights.rbegin()))
			break;
		
		if (!DemoSettings::EnableOnlyManualLight)
		{
            const float dt = timer.getElapsedTime().asSeconds();
			lights[0]->getPosition().x = center.x + cos(dt) * autoLightsRadius;
			lights[1]->getPosition().x = center.x - cos(dt) * autoLightsRadius;
			lights[2]->getPosition().y = center.y + sin(dt) * autoLightsRadius;
			lights[3]->getPosition().y = center.y - sin(dt) * autoLightsRadius;
		}

#pragma region Update shadows
		clock.restart();
		for_each(lights.begin(), lights.end(),
			[&] (LightPtr l)
			{
				l->reset();
				l->addOccluders(occluders);
			} );
		cout << "Shadows generation: " << clock.getElapsedTime().asMilliseconds() << endl;
#pragma endregion

		// Draw normally
#pragma region Render
		clock.restart();
		wnd.draw(bgSpr);

		shadowMap.clear(Color(0, 0, 0, 0));
		for_each(lights.begin(), lights.end(), [&] (const LightPtr l) { l->DrawShadows(shadowMap); } );

		shadowMap.display();
		shadowMapSprite.setTexture(shadowMap.getTexture());
		wnd.draw(shadowMapSprite);

		if (DemoSettings::DrawOccluders)
			for_each(occluders.begin(), occluders.end(), [&] (const ShapePtr s) { wnd.draw(*s); } );

		if (DemoSettings::EnableLightsDebugDraw)
			for_each(lights.begin(), lights.end(), [&] (const LightPtr l) { l->DebugDraw(wnd); } );

		cout << "Rendering: " << clock.getElapsedTime().asMilliseconds()  << endl;
#pragma endregion

		wnd.display();
	}

	return 0;
};
