#ifndef SFGE_GRAPHICS_GRAPHIC_SYSTEM_HPP
#define SFGE_GRAPHICS_GRAPHIC_SYSTEM_HPP

#include "sfge/utilities/singleton.hpp"
#include "sfge/infrastructure/infrastructure_fwd.hpp"
#include "sfge/graphics/sfml_drawable_ext.hpp"

#include <map>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace sfge
{
	class GraphicSystem : public sfge::Singleton<GraphicSystem>
	{
	public:
		typedef size_t	LayerIndex;

		struct DrawableEntry
		{
			DrawableEntry(DrawablePtr drawable, ShaderPtr shader = ShaderPtr())
				: mDrawable(drawable), mShader(shader)
			{
			}

			DrawablePtr mDrawable;
			ShaderPtr	mShader;
		};

		struct InitParams
		{
			InitParams()
				:	mMode(800, 600), mWindowTitle("SFGE Window"),
					mStyle(sf::Style::Default), mHandle(nullptr),
					mFrameRateLimit(60)
			{
			}

			sf::VideoMode		mMode;
			const std::string	mWindowTitle;
			unsigned long		mStyle;
			sf::ContextSettings	mContextSettings;
			
			sf::WindowHandle	mHandle;

			unsigned int		mFrameRateLimit;
		};

	public:
		static void Init();

		~GraphicSystem();

		void Create(const InitParams &params);
		bool IsMainWindowOpened();

		void SetGame(Game *g)		{ mGame = g; }

		sf::RenderWindow& GetCurrentRenderWindow();
		sf::RenderTarget& GetCurrentRenderTarget();

		void AddDrawableToLayer(LayerIndex layer, DrawablePtr drawable);

		void UpdateEvents();
		void PreRender();
		void PostRender();

	private:
		typedef std::multimap<LayerIndex, DrawableEntry>	LayeredDrawables;

	private:
		GraphicSystem();

	private:
		sf::RenderWindow	mRenderWindow;
		Game *				mGame;
		LayeredDrawables	mDrawables;
	};

	GraphicSystem* Singleton<GraphicSystem>::ms_Singleton(nullptr);
}

#endif
