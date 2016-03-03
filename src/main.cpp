#include<iostream>
#include<SDL.h>
#include<GL/glew.h>
#include<SDL_opengl.h>
#include "config.hpp"

#include "md2.hpp"

// TODO (sean): Create settings to change screen resolution instead of defines
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

bool init(); // Initialise SDL and base OpenGL
bool initGL(); // Initialise matrices and clear Colour for OpenGL
void render(); // Render the screen
void close(); // Run before close to clear variables

// Window we render to
SDL_Window *window = NULL;
// OpenGL context
SDL_GLContext context = NULL;

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

			render();

			SDL_GL_SwapWindow(window);
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
		//Use OpenGL 2.1
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		// Create Window
		window = SDL_CreateWindow("Dung3on", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);

		if (window == NULL)
		{
			std::cout << "SDL failed to create window. SDL error: " << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			// Create GL context
			context = SDL_GL_CreateContext(window);

			if (context == NULL)
			{
				std::cout << "SDL failed to create OpenGL context. SDL error: " << SDL_GetError() << std::endl;
				return false;
			}
			else
			{
				// Initialise GLEW
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					std::cout << "Unable to initialise GLEW. GLEW error: " << glewGetErrorString(glewError) << std::endl;
					return false;
				}

				//Use Vsync
				if( SDL_GL_SetSwapInterval( 1 ) < 0 )
				{
					std::cout << "SDL failed to set vsync. SDL error: " << SDL_GetError() << std::endl;
				}

				// Initialise OpenGL
				if (!initGL())
				{
					std::cout << "Unable to initialise OpenGL" << std::endl;
					return false;
				}
			}
		}
	}

	return true;
}

bool initGL()
{
	GLenum glError = GL_NO_ERROR;

	// Initialise projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error: " << gluErrorString(glError) << std::endl;
		return false;
	}

	// Initialise modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error: " << gluErrorString(glError) << std::endl;
		return false;
	}

	// Set clear colour
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error: " << gluErrorString(glError) << std::endl;
		return false;
	}

	return true;
}

void render()
{
	// Clear screen before rendering next frame
	glClear(GL_COLOR_BUFFER_BIT);

	md2 testModel("./asset/model/player_test.md2");
	testModel.renderFrame(0);
}

void close()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;
	context = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}
