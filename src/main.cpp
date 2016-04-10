#include<iostream>
#include<SDL.h>
#include<GL/glew.h>
#include<SDL_opengl.h>

#include "config.hpp"

#include "game.hpp"
#include "md2.hpp"
#include "resourcemanager.hpp"

#define FRAMERATE 60

void update(game *theGame); // Update the game logic
void render(game *theGame); // Render the screen

int main(int argc, char *argv[])
{
	game theGame;

	std::cout << "Hello World! This is Version " << VERSION_MAJOR << "." << VERSION_MINOR << std::endl;

	if (!theGame.init())
	{
		std::cout << "Failed to Initialise..." << std::endl;
	}
	else
	{
		// boolean is true while running, gets set to false when we want to exit.
		bool running = true;

		// SDL event handler
		SDL_Event event;

		controls gameControls;

		theGame.getCurrentMap()->generateMap();

		Uint32 lastFrameTick = SDL_GetTicks();

		while (running)
		{
			Uint32 currentTick = SDL_GetTicks();
			if (lastFrameTick - currentTick > 1000/FRAMERATE)
			{
				lastFrameTick = currentTick;
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
							case SDLK_UP:
								gameControls.pressButton(BUTTON_UP);
								break;
							case SDLK_RIGHT:
								gameControls.pressButton(BUTTON_RIGHT);
								break;
							case SDLK_LEFT:
								gameControls.pressButton(BUTTON_LEFT);
								break;
							case SDLK_DOWN:
								gameControls.pressButton(BUTTON_DOWN);
								break;
							case SDLK_ESCAPE:
								running = false;
								break;
							case SDLK_RETURN:
							case SDLK_RETURN2:
								theGame.getCurrentMap()->generateMap();
								break;
							default:
								break;
						}
					}
					else if (event.type == SDL_KEYUP)
					{
						switch(event.key.keysym.sym)
						{
							case SDLK_UP:
								gameControls.unpressButton(BUTTON_UP);
								break;
							case SDLK_RIGHT:
								gameControls.unpressButton(BUTTON_RIGHT);
								break;
							case SDLK_LEFT:
								gameControls.unpressButton(BUTTON_LEFT);
								break;
							case SDLK_DOWN:
								gameControls.unpressButton(BUTTON_DOWN);
								break;
							default:
								break;
						}
					}
				}
				theGame.update(gameControls);

				gameControls.updateheldButtons();

				theGame.render();

				theGame.swapWindow();
			}
		}
	}

	return 0;
}
