#pragma once
/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment (lib, "glew32.lib")
#endif // !OPENGL_INCLUDES

#include "GameObject.h"

#include "BitMapFile.h"
#include<glm/gtx/rotate_vector.hpp>

#define PI 3.14159265358979324

class Billboard : public GameObject
{
public:
	Billboard(glm::vec3 pos, GameObject * player, float resX, float resY, std::string imageAddress);
	~Billboard();
	BitMapFile * image;
	GameObject * player;
	std::string imageAddress;
	unsigned int texture[1];
	void setup(void);
	void drawScene(void);
	void loadTexture();
	void start(void);
	void update(int deltaTime);
	float resX;
	float resY;
};

