#include<iostream>
#include<fstream>

#include "md2.hpp"

// precalculated normals table
vec3 md2::normalTable[] = {
{ -0.525731f,  0.000000f,  0.850651f },
{ -0.442863f,  0.238856f,  0.864188f },
{ -0.295242f,  0.000000f,  0.955423f },
{ -0.309017f,  0.500000f,  0.809017f },
{ -0.162460f,  0.262866f,  0.951056f },
{  0.000000f,  0.000000f,  1.000000f },
{  0.000000f,  0.850651f,  0.525731f },
{ -0.147621f,  0.716567f,  0.681718f },
{  0.147621f,  0.716567f,  0.681718f },
{  0.000000f,  0.525731f,  0.850651f },
{  0.309017f,  0.500000f,  0.809017f },
{  0.525731f,  0.000000f,  0.850651f },
{  0.295242f,  0.000000f,  0.955423f },
{  0.442863f,  0.238856f,  0.864188f },
{  0.162460f,  0.262866f,  0.951056f },
{ -0.681718f,  0.147621f,  0.716567f },
{ -0.809017f,  0.309017f,  0.500000f },
{ -0.587785f,  0.425325f,  0.688191f },
{ -0.850651f,  0.525731f,  0.000000f },
{ -0.864188f,  0.442863f,  0.238856f },
{ -0.716567f,  0.681718f,  0.147621f },
{ -0.688191f,  0.587785f,  0.425325f },
{ -0.500000f,  0.809017f,  0.309017f },
{ -0.238856f,  0.864188f,  0.442863f },
{ -0.425325f,  0.688191f,  0.587785f },
{ -0.716567f,  0.681718f, -0.147621f },
{ -0.500000f,  0.809017f, -0.309017f },
{ -0.525731f,  0.850651f,  0.000000f },
{  0.000000f,  0.850651f, -0.525731f },
{ -0.238856f,  0.864188f, -0.442863f },
{  0.000000f,  0.955423f, -0.295242f },
{ -0.262866f,  0.951056f, -0.162460f },
{  0.000000f,  1.000000f,  0.000000f },
{  0.000000f,  0.955423f,  0.295242f },
{ -0.262866f,  0.951056f,  0.162460f },
{  0.238856f,  0.864188f,  0.442863f },
{  0.262866f,  0.951056f,  0.162460f },
{  0.500000f,  0.809017f,  0.309017f },
{  0.238856f,  0.864188f, -0.442863f },
{  0.262866f,  0.951056f, -0.162460f },
{  0.500000f,  0.809017f, -0.309017f },
{  0.850651f,  0.525731f,  0.000000f },
{  0.716567f,  0.681718f,  0.147621f },
{  0.716567f,  0.681718f, -0.147621f },
{  0.525731f,  0.850651f,  0.000000f },
{  0.425325f,  0.688191f,  0.587785f },
{  0.864188f,  0.442863f,  0.238856f },
{  0.688191f,  0.587785f,  0.425325f },
{  0.809017f,  0.309017f,  0.500000f },
{  0.681718f,  0.147621f,  0.716567f },
{  0.587785f,  0.425325f,  0.688191f },
{  0.955423f,  0.295242f,  0.000000f },
{  1.000000f,  0.000000f,  0.000000f },
{  0.951056f,  0.162460f,  0.262866f },
{  0.850651f, -0.525731f,  0.000000f },
{  0.955423f, -0.295242f,  0.000000f },
{  0.864188f, -0.442863f,  0.238856f },
{  0.951056f, -0.162460f,  0.262866f },
{  0.809017f, -0.309017f,  0.500000f },
{  0.681718f, -0.147621f,  0.716567f },
{  0.850651f,  0.000000f,  0.525731f },
{  0.864188f,  0.442863f, -0.238856f },
{  0.809017f,  0.309017f, -0.500000f },
{  0.951056f,  0.162460f, -0.262866f },
{  0.525731f,  0.000000f, -0.850651f },
{  0.681718f,  0.147621f, -0.716567f },
{  0.681718f, -0.147621f, -0.716567f },
{  0.850651f,  0.000000f, -0.525731f },
{  0.809017f, -0.309017f, -0.500000f },
{  0.864188f, -0.442863f, -0.238856f },
{  0.951056f, -0.162460f, -0.262866f },
{  0.147621f,  0.716567f, -0.681718f },
{  0.309017f,  0.500000f, -0.809017f },
{  0.425325f,  0.688191f, -0.587785f },
{  0.442863f,  0.238856f, -0.864188f },
{  0.587785f,  0.425325f, -0.688191f },
{  0.688191f,  0.587785f, -0.425325f },
{ -0.147621f,  0.716567f, -0.681718f },
{ -0.309017f,  0.500000f, -0.809017f },
{  0.000000f,  0.525731f, -0.850651f },
{ -0.525731f,  0.000000f, -0.850651f },
{ -0.442863f,  0.238856f, -0.864188f },
{ -0.295242f,  0.000000f, -0.955423f },
{ -0.162460f,  0.262866f, -0.951056f },
{  0.000000f,  0.000000f, -1.000000f },
{  0.295242f,  0.000000f, -0.955423f },
{  0.162460f,  0.262866f, -0.951056f },
{ -0.442863f, -0.238856f, -0.864188f },
{ -0.309017f, -0.500000f, -0.809017f },
{ -0.162460f, -0.262866f, -0.951056f },
{  0.000000f, -0.850651f, -0.525731f },
{ -0.147621f, -0.716567f, -0.681718f },
{  0.147621f, -0.716567f, -0.681718f },
{  0.000000f, -0.525731f, -0.850651f },
{  0.309017f, -0.500000f, -0.809017f },
{  0.442863f, -0.238856f, -0.864188f },
{  0.162460f, -0.262866f, -0.951056f },
{  0.238856f, -0.864188f, -0.442863f },
{  0.500000f, -0.809017f, -0.309017f },
{  0.425325f, -0.688191f, -0.587785f },
{  0.716567f, -0.681718f, -0.147621f },
{  0.688191f, -0.587785f, -0.425325f },
{  0.587785f, -0.425325f, -0.688191f },
{  0.000000f, -0.955423f, -0.295242f },
{  0.000000f, -1.000000f,  0.000000f },
{  0.262866f, -0.951056f, -0.162460f },
{  0.000000f, -0.850651f,  0.525731f },
{  0.000000f, -0.955423f,  0.295242f },
{  0.238856f, -0.864188f,  0.442863f },
{  0.262866f, -0.951056f,  0.162460f },
{  0.500000f, -0.809017f,  0.309017f },
{  0.716567f, -0.681718f,  0.147621f },
{  0.525731f, -0.850651f,  0.000000f },
{ -0.238856f, -0.864188f, -0.442863f },
{ -0.500000f, -0.809017f, -0.309017f },
{ -0.262866f, -0.951056f, -0.162460f },
{ -0.850651f, -0.525731f,  0.000000f },
{ -0.716567f, -0.681718f, -0.147621f },
{ -0.716567f, -0.681718f,  0.147621f },
{ -0.525731f, -0.850651f,  0.000000f },
{ -0.500000f, -0.809017f,  0.309017f },
{ -0.238856f, -0.864188f,  0.442863f },
{ -0.262866f, -0.951056f,  0.162460f },
{ -0.864188f, -0.442863f,  0.238856f },
{ -0.809017f, -0.309017f,  0.500000f },
{ -0.688191f, -0.587785f,  0.425325f },
{ -0.681718f, -0.147621f,  0.716567f },
{ -0.442863f, -0.238856f,  0.864188f },
{ -0.587785f, -0.425325f,  0.688191f },
{ -0.309017f, -0.500000f,  0.809017f },
{ -0.147621f, -0.716567f,  0.681718f },
{ -0.425325f, -0.688191f,  0.587785f },
{ -0.162460f, -0.262866f,  0.951056f },
{  0.442863f, -0.238856f,  0.864188f },
{  0.162460f, -0.262866f,  0.951056f },
{  0.309017f, -0.500000f,  0.809017f },
{  0.147621f, -0.716567f,  0.681718f },
{  0.000000f, -0.525731f,  0.850651f },
{  0.425325f, -0.688191f,  0.587785f },
{  0.587785f, -0.425325f,  0.688191f },
{  0.688191f, -0.587785f,  0.425325f },
{ -0.955423f,  0.295242f,  0.000000f },
{ -0.951056f,  0.162460f,  0.262866f },
{ -1.000000f,  0.000000f,  0.000000f },
{ -0.850651f,  0.000000f,  0.525731f },
{ -0.955423f, -0.295242f,  0.000000f },
{ -0.951056f, -0.162460f,  0.262866f },
{ -0.864188f,  0.442863f, -0.238856f },
{ -0.951056f,  0.162460f, -0.262866f },
{ -0.809017f,  0.309017f, -0.500000f },
{ -0.864188f, -0.442863f, -0.238856f },
{ -0.951056f, -0.162460f, -0.262866f },
{ -0.809017f, -0.309017f, -0.500000f },
{ -0.681718f,  0.147621f, -0.716567f },
{ -0.681718f, -0.147621f, -0.716567f },
{ -0.850651f,  0.000000f, -0.525731f },
{ -0.688191f,  0.587785f, -0.425325f },
{ -0.587785f,  0.425325f, -0.688191f },
{ -0.425325f,  0.688191f, -0.587785f },
{ -0.425325f, -0.688191f, -0.587785f },
{ -0.587785f, -0.425325f, -0.688191f },
{ -0.688191f, -0.587785f, -0.425325f }
};

int md2::md2Ident = 'I' + ('D'<<8) + ('P'<<16) + ('2'<<24);
int md2::md2Version = 8;

// Constructor loads the model
md2::md2(const std::string &filename)
{
	std::ifstream file(filename.c_str(), std::ios::binary);

	// Read header
	file.read((char *)&header, sizeof (md2_header)); // read the contents of the header into the header variable

	if (header.ident != md2Ident)
		std::cout << "WARNING: Bad MD2 ident for file: " << filename << std::endl;

	if (header.version != md2Version)
		std::cout << "WARNING: Bad MD2 version for file: " << filename << std::endl;

	skins = new md2_skin[header.num_skins];
	texCoords = new md2_texCoord[header.num_texCoords];
	triangles = new md2_triangle[header.num_triangles];
	frames = new md2_frame[header.num_frames];
	glcmds = new int[header.num_glcmds];

	scale = 1.0f;

	// Read skins
	file.seekg(header.offset_skins, std::ios::beg); // seek to where skin data begins
	file.read(reinterpret_cast<char *>(skins), sizeof(md2_skin) * header.num_skins); // read the contents up to the end of the skins into the skins array

	// Read texture coordinates
	file.seekg(header.offset_texCoords, std::ios::beg);
	file.read(reinterpret_cast<char *>(texCoords), sizeof(md2_texCoord) * header.num_texCoords);

	// Read triangles
	file.seekg(header.offset_triangles, std::ios::beg);
	file.read(reinterpret_cast<char *>(triangles), sizeof(md2_triangle) * header.num_triangles);

	// Read frames
	file.seekg(header.offset_frames, std::ios::beg);
    for (int i = 0; i < header.num_frames; i++)
    {
		// Allocate space for frame's vertices
		frames[i].vertices = new md2_vertex[header.num_vertices];

		// Frame data
		file.read(reinterpret_cast<char *>(frames[i].scale), sizeof(vec3));
		file.read(reinterpret_cast<char *>(frames[i].translate), sizeof(vec3));
		file.read(reinterpret_cast<char *>(frames[i].name), sizeof(char) * 16); // 16 characters in frame name
		file.read(reinterpret_cast<char *>(frames[i].vertices), sizeof(md2_vertex) * header.num_vertices);
    }

	// Read GL commands
	file.seekg(header.offset_glcmds, std::ios::beg);
	file.read(reinterpret_cast<char *>(glcmds), sizeof(int) * header.num_glcmds); // the numbers are read in as integers

	file.close();
}

void md2::renderFrame(int frame)
{
	// TODO (sean): Use Vertex Arrays for drawing instead of old glBegin/glEnd

	// store old matrix (we need to store the old matrix and bring it back because MD2s are rotated oddly
	glPushMatrix();

	// reverse orientation of front facing polygons
	glPushAttrib(GL_POLYGON_BIT);
	glFrontFace(GL_CW);

    if (frame < 0 || frame > header.num_frames)
		return;

	int i;
	int *pGlcmds = glcmds; // pointer to glcmds so we don't change original pointer
	GLfloat lightPos[] = {0.0f, 1.0f, 0.0f, 0.0f}; // light position
	GLfloat diffuseColour[] = {1.0f, 1.0f, 1.0f, 1.0f}; // diffuse light colour
	GLfloat ambientColour[] = {1.0f, 1.0f, 1.0f, 1.0f}; // ambient light colour
	GLuint textureID;

	// TODO (sean): Remove translate, it's just for testing
	glTranslatef(0.0f, -0.2f, -5.0f);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseColour);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambientColour);

	glRotatef(0.05f * SDL_GetTicks(), 0.0f, 1.0f, 0.0f);

	//glScalef(0.3f, 0.3f, 0.3f);

	textureID = loadTexture("./asset/texture/player_test.png");

    while ((i = *(pGlcmds++)) != 0)
    {
		if (i < 0)
		{
			glBegin(GL_TRIANGLE_FAN);
			i = -i;
		}
		else
		{
			glBegin(GL_TRIANGLE_STRIP);
		}

		for (; i > 0; i--, pGlcmds += 3)
		{
			// pGlcmds[0] : final S texture coord.
			// pGlcmds[1] : final T texture coord.
			// pGlcmds[2] : vertex index to draw

			md2_glcmd *pGlcmd = reinterpret_cast<md2_glcmd *>(pGlcmds); // glcmd for the vertex
			md2_frame *pFrame = &frames[frame]; // frame to draw
			md2_vertex *pVert = &pFrame->vertices[pGlcmd->index]; // vertex index

			// Send texture co-ordinates
			glTexCoord2f(pGlcmd->s, 1.0f - pGlcmd->t);

			// Use the normals from the precalculated table
			glNormal3fv(normalTable[pVert->lightNormalIndex]);

			vec3 vertex;
			vertex[0] = (pFrame->scale[0] * pVert->vertex[0] + pFrame->translate[0]) * scale;
			vertex[1] = (pFrame->scale[2] * pVert->vertex[2] + pFrame->translate[2]) * scale;
			vertex[2] = -1 * (pFrame->scale[1] * pVert->vertex[1] + pFrame->translate[1]) * scale;

			glVertex3fv(vertex);
		}
		glEnd();
    }
    glDeleteTextures(1, &textureID);

    glPopAttrib(); // GL_POLYGON_BIT
    glPopMatrix();
}

GLuint md2::loadTexture(const std::string &filename)
{
	SDL_Surface *surface;
	GLuint textureId;
	GLuint mode;

	surface = IMG_Load(filename.c_str());

	if (!surface)
		return 0;

	if (surface->format->BytesPerPixel == 3)
		mode = GL_RGB;
	else if (surface->format->BytesPerPixel == 4)
		mode = GL_RGBA;
	else
	{
		SDL_FreeSurface(surface);
	}

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

    return textureId;
}

md2::~md2()
{
	delete [] skins;
	delete [] texCoords;
	delete [] triangles;
	delete [] frames;
	delete [] glcmds;
}
