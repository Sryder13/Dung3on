#include<iostream>

#include "game.hpp"

game::game()
{
	window = NULL;
	context = NULL;
	currentMap = new gamemap;
}

bool game::init()
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

bool game::initGL()
{
	GLenum glError = GL_NO_ERROR;

	// Initialise projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// setup viewport
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	// setup perspective
	gluPerspective(45.0f, (float)SCREEN_WIDTH/SCREEN_HEIGHT, 0.1f, 100.0f);

	// Initialise modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set clear colour
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glShadeModel(GL_SMOOTH); // smooth models
	glClearDepth(1.0f); // what the depth buffer is cleared to each frame
	glEnable(GL_DEPTH_TEST); // enable depth testing
	glDepthFunc(GL_LEQUAL); // when incoming pixels are less than or equal to old once they are drawn
	glEnable(GL_TEXTURE_2D); // enable textures
	glEnable(GL_CULL_FACE); // enable face culling (not drawing back faces)
	glCullFace(GL_BACK); // cull back faces
	glEnable(GL_LIGHTING); // enable lighting
	glEnable(GL_LIGHT0); // enable light 0

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // nice perspective correction hint

	glError = glGetError();
	if (glError != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error: " << gluErrorString(glError) << std::endl;
		return false;
	}

	return true;
}

game::~game()
{
	//Destroy window
	SDL_DestroyWindow(window);
	window = NULL;
	context = NULL;

	// delete all resources
	resourcemanager::getResourceManager()->clearResources();
	delete currentMap;

	//Quit SDL subsystems
	SDL_Quit();
}
