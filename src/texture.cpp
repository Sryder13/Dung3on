#include "texture.hpp"

texture::texture()
{
	//ctor
}

bool texture::load(const std::string &filename)
{
	SDL_Surface *surface;
	GLuint mode;

	surface = IMG_Load(filename.c_str());

	if (!surface)
	{
		std::cout << "texture::texture: Texture file not found" << std::endl;
		return false;
	}

	if (surface->format->BytesPerPixel == 3)
		mode = GL_RGB;
	else if (surface->format->BytesPerPixel == 4)
		mode = GL_RGBA;
	else
	{
		SDL_FreeSurface(surface);
		return false;
	}

	this->filename = filename;

	// Generate one texture name for use
	glGenTextures(1, &textureId);

	// We want to be using this texture
	glBindTexture(GL_TEXTURE_2D, textureId);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); // filter when too small is linear
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // filter when magnified is nearest

	if (GLEW_SGIS_generate_mipmap)
	{
		// Hardware mipmap generation
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		glHint(GL_GENERATE_MIPMAP_HINT_SGIS, GL_NICEST);

		// Put the texture into OpenGL
		glTexImage2D(GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);
	}
	else
	{
		// no hardware mipmaps so use gluBuild2DMupmaps
		gluBuild2DMipmaps(GL_TEXTURE_2D, mode, surface->w, surface->h, mode, GL_UNSIGNED_BYTE, surface->pixels);
	}

	SDL_FreeSurface(surface); // no longer need the SDL surface
	return true;
}

texture::~texture()
{
	glDeleteTextures(1, &textureId);
}
