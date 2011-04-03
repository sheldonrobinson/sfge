#ifndef SFGE_GRAPHICS_GRAPHIC_SYSTEM_HPP
#define SFGE_GRAPHICS_GRAPHIC_SYSTEM_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "sfge/utilities/singleton.hpp"
#include "sfge/infrastructure/infrastructure_fwd.hpp"

namespace sfge
{
	class GraphicSystem : public sfge::Singleton<GraphicSystem>
	{
	public:
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

		const sf::Input& GetInput();
		sf::RenderTarget& GetCurrentRenderTarget();

		void UpdateEvents();
		void PreRender();
		void PostRender();

	private:
		GraphicSystem();

	private:
		sf::RenderWindow	mRenderWindow;
		Game *				mGame;
	};

	GraphicSystem* Singleton<GraphicSystem>::ms_Singleton(nullptr);
}

#endif
