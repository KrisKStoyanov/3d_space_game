#pragma once
/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif 

#include "Collider.h"

class CubeCollider : public Collider
{
private:
	bool trigger = false;
public:
	CubeCollider(glm::vec3 * centre, float cubeWidth, float cubeHeight, float cubeLength);
	~CubeCollider();
	float minX();
	float maxX();
	float minY();
	float maxY();
	float minZ();
	float maxZ();
	bool collidesWith(Collider * other);
	float length = 0.0, width = 0.0, height = 0.0;
	void Draw();
};


