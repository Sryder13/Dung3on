#ifndef GAME_H
#define GAME_H

#include<SDL.h>
#include<GL/glew.h>

#include<cmath>

#include "resourcemanager.hpp"
#include "gamemap.hpp"
#include "controls.hpp"

// TODO (sean): Create settings to change screen resolution instead of defines
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

class game
{
	public:
		game();
		virtual ~game();

		bool init(); // initialise window etc.
		bool initGL(); // initialise GL
		void swapWindow() {SDL_GL_SwapWindow(window);}
		void update(controls gameControls);
		void render();

		gamemap *getCurrentMap() {return currentMap;}
	protected:
	private:
		SDL_Window *window; // Window we render to
		SDL_GLContext context; // OpenGL context
		gamemap *currentMap;
};

#endif // GAME_H
