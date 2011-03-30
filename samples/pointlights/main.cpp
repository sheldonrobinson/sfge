#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>

#include <boost/array.hpp>
#include <boost/static_assert.hpp>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <sfge/graphics/sfml_shape_ext.hpp>
#include <sfge/graphics/light.hpp>

namespace DemoSettings
{
	static const bool	EnableFrameRateLimit	= false;
	static const int	FrameRateLimit			= 60;

	static const bool	UseBigBugOccluder		= true;
	static const bool	UseSpheresAsOccluders	= false;
	static const int	OccludersCount			= 125;
	static const float	OccludersRange			= 275;

	static const float	DefaultLightsRadius		= 250;
	static const int	WheelFactorToLightRad	= 5;

	static const bool	EnableManualLight		= false;
	static const bool	EnableOnlyManualLight	= false;
	BOOST_STATIC_ASSERT(!EnableOnlyManualLight || (EnableOnlyManualLight && EnableManualLight));

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
	while (wnd.GetEvent(evt))
	{
		switch(evt.Type)
		{
		case Event::Closed:
			return true;
			break;

		case Event::KeyPressed:
			switch(evt.Key.Code)
			{
			case Key::Escape:
				return true;
				break;

			case Key::F1:
				DemoSettings::DrawOccluders = !DemoSettings::DrawOccluders;
				break;

			case Key::F2:
				DemoSettings::EnableLightsDebugDraw = !DemoSettings::EnableLightsDebugDraw;
				break;

			case Key::F3:
				DemoSettings::EnableShadowsOutline = !DemoSettings::EnableShadowsOutline;
				break;
			}
			break;

		case Event::MouseMoved:
			if (DemoSettings::EnableManualLight)
				light->setPosition(Vector2f(static_cast<float>(evt.MouseMove.X),
									   static_cast<float>(evt.MouseMove.Y)));
			break;

		case Event::MouseWheelMoved:
			if (DemoSettings::EnableManualLight)
				light->getRadius() += evt.MouseWheel.Delta * DemoSettings::WheelFactorToLightRad;
			break;
		}
	}

	return false;
}

int main(int argc, char **argv)
{
	RenderWindow wnd(VideoMode(800, 600), "Test dynamic lights");
	if (DemoSettings::EnableFrameRateLimit)
		wnd.SetFramerateLimit(DemoSettings::FrameRateLimit);
	wnd.Show(true);

	Image bgImg;
	bgImg.LoadFromFile("data/grass.png");
	Sprite bgSpr(bgImg);

#pragma region Generate some occluders
	Shapes occluders(DemoSettings::OccludersCount);
	const Vector2f center(400, 300);
	const float r = DemoSettings::OccludersRange;
	const float td = 3.141592f * 2 / occluders.size();
	float t = 0.f;
	auto getNextOccPos = [&] () -> Vector2f { Vector2f p(cos(t) * r, sin(t) * r); t += td; return p + center; };
	if (DemoSettings::UseBigBugOccluder)
	{
		occluders[0] = ShapePtr(new Shape(Shape::Rectangle(400, 300, 250.f, 50.f, Color::Cyan)));
		occluders.resize(1);
	}
	else if (DemoSettings::UseSpheresAsOccluders)
	{
		generate(occluders.begin(), occluders.end(),
			[&] () -> ShapePtr
			{
				ShapePtr s(new Shape(Shape::Circle(0, 0, 6.f, Color::Cyan)));
				s->SetPosition(getNextOccPos());
				return s;
			} );
	}
	else
	{
		generate(occluders.begin(), occluders.end(),
			[&] () -> ShapePtr
			{
				ShapePtr s(new Shape(Shape::Rectangle(0, 0, 6.f, 6.f, Color::Cyan)));
				s->SetPosition(getNextOccPos());
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
	
	if (DemoSettings::EnableManualLight)
		lights.push_back(LightPtr(new Light(center, DemoSettings::DefaultLightsRadius)));
	const float autoLightsRadius = DemoSettings::OccludersRange - DemoSettings::DefaultLightsRadius * 0.5f;
#pragma endregion

	RenderImage shadowMap;
	shadowMap.Create(800, 600);
	Sprite shadowMapSprite;

	sf::Clock timer;
	sf::Clock clock;
	while (wnd.IsOpened())
	{
		if (handleEvents(wnd, *lights.rbegin()))
			break;
		
		if (!DemoSettings::EnableOnlyManualLight)
		{
			lights[0]->getPosition().x = center.x + cos(timer.GetElapsedTime()) * autoLightsRadius;
			lights[1]->getPosition().x = center.x - cos(timer.GetElapsedTime()) * autoLightsRadius;
			lights[2]->getPosition().y = center.y + sin(timer.GetElapsedTime()) * autoLightsRadius;
			lights[3]->getPosition().y = center.y - sin(timer.GetElapsedTime()) * autoLightsRadius;
		}

#pragma region Update shadows
		clock.Reset();
		for_each(lights.begin(), lights.end(),
			[&] (LightPtr l)
			{
				l->reset();
				l->addOccluders(occluders);
			} );
		cout << "Shadows generation: " << clock.GetElapsedTime() * 1000 << endl;
#pragma endregion

		// Draw normally
#pragma region Render
		clock.Reset();
		wnd.Draw(bgSpr);

		shadowMap.Clear(Color(0, 0, 0, 0));
		for_each(lights.begin(), lights.end(), [&] (const LightPtr l) { l->DrawShadows(shadowMap); } );

		shadowMap.Display();
		shadowMapSprite.SetImage(shadowMap.GetImage());
		wnd.Draw(shadowMapSprite);

		if (DemoSettings::DrawOccluders)
			for_each(occluders.begin(), occluders.end(), [&] (const ShapePtr s) { wnd.Draw(*s); } );

		if (DemoSettings::EnableLightsDebugDraw)
			for_each(lights.begin(), lights.end(), [&] (const LightPtr l) { l->DebugDraw(wnd); } );

		cout << "Rendering: " << clock.GetElapsedTime() * 1000 << endl;
#pragma endregion

		wnd.Display();
	}

	return 0;
};
