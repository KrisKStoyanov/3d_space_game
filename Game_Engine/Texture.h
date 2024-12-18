#pragma once
/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment (lib, "glew32.lib")
#endif // !OPENGL_INCLUDES

#include "BitMapFile.h"

#define PI 3.14159265358979324

class Texture
{
public:
	Texture(std::string imageAddress, float sphereSize);
	~Texture();

	float size;

	std::string imageAddress;
	BitMapFile *image;

	int p = 30; //grid rows
	int q = 30; //grid columns
	float *vertices = NULL;
	float *normals = NULL;
	float *textureCoordinates = NULL;
	unsigned int texture[1];

	void LoadExternalTextures();
	float f(int i, int j);
	float g(int i, int j);
	float h(int i, int j);

	float fn(int i, int j);
	float gn(int i, int j);
	float hn(int i, int j);

	void fillVertexArray(void);
	void fillNormalArray(void);
	void fillTextureCoordArray(void);

	void setup(void);
	void drawScene(void);
};



