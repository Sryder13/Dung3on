#include<iostream>
#include<SDL.h>
#include "config.hpp"

// TODO (sean): Create settings to change screen resolution instead of defines
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

bool init();
void close();

// Window we render to
SDL_Window *window = NULL;
// Surface containing the window
SDL_Surface *screenSurface = NULL;

int main(int argc, char *argv[])
{
	std::cout << "Hello World! This is Version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;

	if (!init())
	{
		std::cout << "Failed to Initialise..." << std::endl;
	}
	else
	{
		// boolean is true while running, gets set to false when we want to exit.
		bool running = true;

		// SDL event handler
		SDL_Event event;

		while (running)
		{
			// Poll events from SDL
			while (SDL_PollEvent(&event) != 0)
			{
				//User requests quit
				if (event.type == SDL_QUIT)
				{
					running = false;
				}
				else if (event.type == SDL_KEYDOWN)
				{
					switch(event.key.keysym.sym)
					{
						case SDLK_ESCAPE:
							running = false;
							break;
						default:
							break;
					}
				}
			}
		}
	}

	close();

	return 0;
}

bool init()
{
	// Initialise SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL failed to initialise. SDL error: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		// Create Window
		window = SDL_CreateWindow("Dung3on", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			std::cout << "SDL failed to create window. SDL error: " << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			// Get Window Surface
            screenSurface = SDL_GetWindowSurface(window);

			// Fill surface with white
            SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			// Update Window
            SDL_UpdateWindowSurface(window);
		}
	}

	return true;
}

void close()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;
	screenSurface = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
