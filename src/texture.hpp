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
		texture();
		virtual ~texture();

		bool load(const std::string &filename);
		void bindTex() {glBindTexture(GL_TEXTURE_2D, textureId);}

		std::string getFilename() {return this->filename;}
	protected:
	private:
		GLuint textureId;
		std::string filename;
};

#endif // TEXTURE_H
