#include<iostream>
#include<SDL.h>
#include<GL/glew.h>
#include<SDL_opengl.h>
#include "config.hpp"

#include "game.hpp"
#include "md2.hpp"

void render(); // Render the screen

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

			render();

			theGame.swapWindow();
		}
	}

	return 0;
}

void render()
{
	// reset modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Clear screen before rendering next frame
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	md2 testModel("./asset/model/sphere_test.md2");
	testModel.renderFrame(0);
}
