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

class SphereCollider : public Collider
{
public:
	SphereCollider(glm::vec3 * centre, int points, float width, float height, float length);
	~SphereCollider();
	float minX();
	float maxX();
	float minY();
	float maxY();
	float minZ();
	float maxZ();
	bool collidesWith(Collider * other);
	int points;
	float length = 0.0, width = 0.0, height = 0.0;
	void Draw();
};

