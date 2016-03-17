#ifndef GAME_H
#define GAME_H

#include<SDL.h>
#include<GL/glew.h>
#include<SDL_opengl.h>

#include "resourcemanager.hpp"

// TODO (sean): Create settings to change screen resolution instead of defines
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class game
{
    public:
		game();
		virtual ~game();

		bool init();
		bool initGL();
		void swapWindow() {SDL_GL_SwapWindow(window);}
    protected:
    private:
		SDL_Window *window; // Window we render to
		SDL_GLContext context; // OpenGL context
};

#endif // GAME_H
