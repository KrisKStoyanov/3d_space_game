#include "Ring.h"

#define PI 3.14159265358979324

Ring::Ring(glm::vec3 position, Color col, float innerR, float outerR) : GameObject(position)
{
	this->position = position;
	this->color = color;
	this->innerR = innerR;
	this->outerR = outerR;
}


Ring::~Ring()
{
}

void Ring::setup()
{
	float matArray[] = { 1.0, 1.0, 1.0, 1.0 };

	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glMaterialfv(GL_FRONT, GL_AMBIENT, matArray);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, matArray);

	// Create texture ids.
	glGenTextures(1, texture);

	// Load launch texture.
	LoadExternalTextures();

	// Specify how texture values combine with current surface color values.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Turn on OpenGL texturing.
	glEnable(GL_TEXTURE_2D);

	// Allocate space for vertex and texture coordinates arrays.
	vertices = new float[3 * (p + 1)*(q + 1)];
	textureCoordinates = new float[2 * (p + 1)*(q + 1)];

	// Set the array pointers.
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinates);

	// Fill the vertex and texture co-ordinates arrays.
	fillVertexArray();
	fillTextureCoordArray();
}

void Ring::drawScene()
{
	int  i, j;

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(this->position.x, this->position.y, this->position.z);
	glutSolidTorus(innerR, outerR, 40, 40);
	glEnd();
	glPushMatrix();
}

void Ring::start()
{

}

void Ring::update(int deltaTime)
{
	shift += 0.01;
	if (shift > 1.0) shift -= 1.0;
}

void Ring::LoadExternalTextures()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->sizeX, image->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

float Ring::f(int i, int j)
{
	return ((outerR + innerR * cos((-1 + 2 * (float)j / q) * PI)) * cos((-1 + 2 * (float)i / p) * PI));
}

float Ring::g(int i, int j)
{
	return ((outerR + innerR * cos((-1 + 2 * (float)j / q) * PI)) * sin((-1 + 2 * (float)i / p) * PI));
}

float Ring::h(int i, int j)
{
	return (innerR * sin((-1 + 2 * (float)j / q) * PI));
}

void Ring::fillVertexArray(void)
{
	int i, j, k;

	k = 0;
	for (j = 0; j <= q; j++)
		for (i = 0; i <= p; i++)
		{
			vertices[k++] = f(i, j);
			vertices[k++] = g(i, j);
			vertices[k++] = h(i, j);
		}
}

void Ring::fillTextureCoordArray(void)
{
	int i, j, k;

	k = 0;
	for (j = 0; j <= q; j++)
		for (i = 0; i <= p; i++)
		{
			textureCoordinates[k++] = (float)i / p;
			textureCoordinates[k++] = (float)j / q;
		}
}
