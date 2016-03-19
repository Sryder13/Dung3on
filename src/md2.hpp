#ifndef MD2_H
#define MD2_H

#include<GL/glew.h>
#include<SDL_opengl.h>

#include "resourcemanager.hpp"
#include "texture.hpp"

typedef float vec3[3];

struct md2_header // header of the file
{
	int ident; // Magic number: "IDP2"
	int version; // Version: must be 8

	int skinWidth; // Texture width
	int skinHeight; // Texture height

	int frameSize; // Size in bytes of a frame

	int num_skins; // Number of skins
	int num_vertices; // Number of vertices per frame
	int num_texCoords; // Number of texture coordinates
	int num_triangles; // Number of triangles
	int num_glcmds; // Number of opengl commands
	int num_frames; // Number of frames

	int offset_skins; // Offset of skin data
	int offset_texCoords; // Offset of texture coordinate data
	int offset_triangles; // Offset triangle data
	int offset_frames; // Offset frame data
	int offset_glcmds; // Offset OpenGL command data
	int offset_end; // Offset end of file
};

struct md2_skin
{
	char name[64]; // name of the texture
};

struct md2_texCoord
{
	short s; // texture x co-ordinate
	short t; // texture y co-ordinate
};

struct md2_triangle
{
	unsigned short vertex[3]; //index of the vertex
	unsigned short texCoord[3]; // index of texture co-ordinate
};

struct md2_vertex
{
	unsigned char vertex[3]; // xyz position of vertex
	unsigned char lightNormalIndex; // normal index
};

struct md2_frame
{
	~md2_frame() {
		delete [] vertices;
	}

	vec3 scale; // xyz scale of frame
	vec3 translate; // xyz translation of frame
	char name[16]; // frame name
	md2_vertex *vertices; // frame vertex array
};

struct md2_glcmd
{
	int index; // vertex index
	float s; // x texture co-ordinate
	float t; // y texture co-ordinate
};

class md2: public resource
{
	public:
		md2();
		virtual ~md2();

		void load(const std::string &filename);
		void renderFrame(int frame, vec3 position, float rotation);
		void setScale(float scale) {this->scale = scale;}

		std::string getFilename() {return this->filename;}
	protected:
	private:
		static vec3 normalTable[162];
		static int md2Ident;
		static int md2Version;

		// Model data
		md2_header header;
		md2_skin *skins;
		md2_texCoord *texCoords;
		md2_triangle *triangles;
		md2_frame *frames;
		int *glcmds;

		float scale;

		std::string filename;
};

#endif // MD2_H
