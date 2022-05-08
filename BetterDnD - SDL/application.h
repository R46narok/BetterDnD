#pragma once

#define WM_MOUSEWHEEL 0x020A


#include <iostream>
#include "vendor/imgui-1.60/imgui.h"
#include "vendor/imgui-1.60/imgui_impl_sdl_gl3.h"
#include <stdio.h>
#include <GL/glew.h> 
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <thread>
#include <vector>

static int selected = 0;

	class Application
	{
	public:
		Application();
		~Application();
		static bool host;

		void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
		void handleEvents();
		void update();
		void render();
		void renderGui();
		void clean();
		bool running() { return isRunning; }

		static SDL_Event event;
		static SDL_Renderer *renderer;
		static bool isRunning;
		//static SDL_Rect camera;

		enum groupLabels : std::size_t
		{
			groupMap,
			groupPlayers,
			groupEnemies,
			groupPages,
			groupGrid,
			groupGeneratedMap,
			groupGeneratedMapPoly,
			groupAI,
			groupPlayerVisualization,
			groupText,
			groupPages2,
			groupNavBar,
			groupChSheets,
			groupRolls
		};
	private:
		SDL_Window *window;
		SDL_Window *windowGui;
	};

