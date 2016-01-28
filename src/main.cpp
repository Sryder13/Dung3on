#include<iostream>
#include<SDL.h>
#include "config.hpp"

// TODO (sean): Create settings to change screen resolution instead of defines
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

int main(int argc, char *argv[])
{
	std::cout << "Hello World! This is Version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;

	// Window we render to
	SDL_Window *window = NULL;
	// Surface containing the window
	SDL_Surface *screenSurface = NULL;

	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL failed to initialise. SDL error: " << SDL_GetError() << std::endl;
	}
	else
	{
		window = SDL_CreateWindow("Dung3on", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			std::cout << "SDL failed to create window. SDL error: " << SDL_GetError() << std::endl;
		}
		else
		{
            screenSurface = SDL_GetWindowSurface(window);

            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

            SDL_UpdateWindowSurface(window);

            SDL_Delay(2000);
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}
