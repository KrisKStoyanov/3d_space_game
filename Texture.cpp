#include "Texture.h"

Texture::Texture(std::string imageAddress, float sphereSize)
{
	this->imageAddress = imageAddress;
	this->image = getbmp(imageAddress);
	this->size = sphereSize;
}

Texture::~Texture()
{
}

void Texture::LoadExternalTextures()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->sizeX, image->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

float Texture::f(int i, int j)
{
	return (cos((-1 + 2 * (float)i / p) * PI));
}

float Texture::g(int i, int j)
{
	return (sin((-1 + 2 * (float)i / p) * PI));
}

float Texture::h(int i, int j)
{
	return (-1 + 2 * (float)j / q);
}

float Texture::fn(int i, int j)
{
	return (cos((-1 + 2 * (float)i / p) * PI));
}

float Texture::gn(int i, int j)
{
	return (sin((-1 + 2 * (float)i / p) * PI));
}

float Texture::hn(int i, int j)
{
	return (0);
}

void Texture::fillVertexArray(void)
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

void Texture::fillNormalArray(void)
{
	int i, j, k;

	k = 0;
	for (j = 0; j <= q; j++)
		for (i = 0; i <= p; i++)
		{
			normals[k++] = fn(i, j);
			normals[k++] = gn(i, j);
			normals[k++] = hn(i, j);
		}
}

void Texture::fillTextureCoordArray(void)
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

void Texture::setup(void)
{
	glEnable(GL_DEPTH_TEST);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	vertices = new float[3 * (p + 1)*(q + 1)];
	normals = new float[3 * (p + 1)*(q + 1)];
	textureCoordinates = new float[2 * (p + 1)*(q + 1)];
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glNormalPointer(GL_FLOAT, 0, normals);
	glTexCoordPointer(2, GL_FLOAT, 0, textureCoordinates);
	fillVertexArray();
	fillNormalArray();
	fillTextureCoordArray();
	glGenTextures(2, texture);
	LoadExternalTextures();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glEnable(GL_TEXTURE_2D);
}

void Texture::drawScene(void)
{
	glEnable(GL_TEXTURE_2D);

	glColor4f(1, 1, 1, 1);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	if (size != 0) {
		GLUquadricObj *sphere = NULL;
		sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
		gluQuadricTexture(sphere, TRUE);
		gluQuadricNormals(sphere, GLU_SMOOTH);
		gluSphere(sphere, size + size / 5, 20, 20);
	}
	//glBegin(GL_POLYGON);
	//glTexCoord2f(0.0, 0.0);
	//for (int i = 0; i <= p; i++)
	//{
	//	for (int j = 0; j < p; j++) {
	//		glNormal3f(0.0, 0.0, 1.0);
	//		glTexCoord2f(0.5 + 0.5*cos((-1 + 2 * (float)i / p) * PI), 0.5 + 0.5*sin((-1 + 2 * (float)i / p) * PI));
	//		glVertex3f(cos((-1 + 2 * (float)i / p) * PI), sin((-1 + 2 * (float)i / p) * PI), 1);
	//	}
	//}
	//glEnd();

	//glDisable(GL_TEXTURE_2D);
	//glBegin(GL_POLYGON);
	//glTexCoord2f(0.0, 0.0);
	//for (int i = 0; i <= p; i++)
	//{
	//	glNormal3f(0.0, 0.0, 1.0);
	//	glTexCoord2f(0.5 + 0.5*cos((-1 + 2 * (float)i / p) * PI), 0.5 + 0.5*sin((-1 + 2 * (float)i / p) * PI));
	//	glVertex3f(cos((-1 + 2 * (float)i / p) * PI), sin((-1 + 2 * (float)i / p) * PI), 1.0);
	//}
	//glEnd();
}

