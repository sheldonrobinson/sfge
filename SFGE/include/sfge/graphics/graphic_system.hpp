#ifndef SFGE_GRAPHICS_GRAPHIC_SYSTEM_HPP
#define SFGE_GRAPHICS_GRAPHIC_SYSTEM_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "sfge/utilities/singleton.hpp"

namespace sfge
{
	class GraphicSystem : public sfge::Singleton<GraphicSystem>
	{
	public:
		struct InitParams
		{
			InitParams()
				:	mMode(800, 600), mWindowTitle("SFGE Window"),
					mStyle(sf::Style::Default), mHandle(0),
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

		const sf::Input& GetInput();
		sf::RenderTarget& GetCurrentRenderTarget();

		void UpdateEvents();
		void PreRender();
		void PostRender();

	private:
		GraphicSystem();

	private:
		sf::RenderWindow	mRenderWindow;
	};

	GraphicSystem* Singleton<GraphicSystem>::ms_Singleton(0);
}

#endif
