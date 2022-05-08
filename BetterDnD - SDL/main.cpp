
#include "application.h"
#include "utilities/Server.h"
 
Application *app = nullptr;

int main(int argc, char *argv[])
{	
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	app = new Application();
	app->init("BetterD&D", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1154, 760, false);
	while (app->running())
	{
		frameStart = SDL_GetTicks();
		app->handleEvents();
		app->update();
		app->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
	app->clean();
	return 0;

}