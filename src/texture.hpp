#ifndef TEXTURE_H
#define TEXTURE_H

#include<iostream>

#include<GL/glew.h>
#include<SDL_opengl.h>
#include<SDL_image.h>

#include "resourcemanager.hpp"

class texture: public resource
{
	public:
		texture(); // constructor
		virtual ~texture(); // destructor

		bool load(const std::string &filename); // load texture
		void bindTex() {glBindTexture(GL_TEXTURE_2D, textureId);} // set texture to use for gl

		std::string getFilename() {return this->filename;}
	protected:
	private:
		GLuint textureId; // id of the texture
		std::string filename;
};

#endif // TEXTURE_H
