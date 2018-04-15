#pragma once
#include "BitMapFile.h"
#include "GameObject.h"

class Ring : public GameObject
{
public:
	Ring(glm::vec3 position, Color col, float innerR, float outerR);
	~Ring();

	BitMapFile *image = getbmp("./Skybox/astTexture.bmp");

	float innerR;
	float outerR;

	void setup(void);
	void drawScene(void);
	void start();
	void update(int deltaTime);
	int p = 20; // Number of grid columns.
	int q = 20; // Number of grid rows
	float *vertices = NULL; // Vertex array of the mapped sample on the torus.
	float *textureCoordinates = NULL; // Texture co-ordinates array of the mapped sample on the torus.
	unsigned int texture[1]; // Array of texture indices.

	float shift = 0.0; // Texture shift.
	int animationPeriod = 100;

	void LoadExternalTextures();
	float f(int i, int j);
	float g(int i, int j);
	float h(int i, int j);
	void fillVertexArray(void);
	void fillTextureCoordArray(void);

};

