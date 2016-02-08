#ifndef MD2_H
#define MD2_H

struct vec3
{
	float x;
	float y;
	float z;
};

struct vertex
{
	unsigned char v[3];
	unsigned char lightNormalIndex;
};

struct texcoord
{
	short s;
	short t;
};

struct frame
{
	vec3 scale;
	vec3 translate;
	char name[16];
	vertex vert;
};

class md2
{
	public:
		md2();
		virtual ~md2();
	protected:
	private:
	md2_header header;
};

class md2_header
{
	public:
		md2_header();
	protected:
	private:
		int ident;                  /* magic number: "IDP2" */
		int version;                /* version: must be 8 */

		int skinwidth;              /* texture width */
		int skinheight;             /* texture height */

		int framesize;              /* size in bytes of a frame */

		int num_skins;              /* number of skins */
		int num_vertices;           /* number of vertices per frame */
		int num_st;                 /* number of texture coordinates */
		int num_tris;               /* number of triangles */
		int num_glcmds;             /* number of opengl commands */
		int num_frames;             /* number of frames */

		int offset_skins;           /* offset skin data */
		int offset_st;              /* offset texture coordinate data */
		int offset_tris;            /* offset triangle data */
		int offset_frames;          /* offset frame data */
		int offset_glcmds;          /* offset OpenGL command data */
		int offset_end;             /* offset end of file */
};

#endif // MD2_H
