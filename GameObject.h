#pragma once
/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/glext.h>
#pragma comment (lib, "glew32.lib")
#endif // !OPENGL_INCLUDES

#include <iostream>
#include <map>
#include <glm/glm.hpp>
#include "CubeCollider.h"
#include "SphereCollider.h"
#include "Color.h"
#include "Texture.h"
#include "Statistics.h"
#include<glm/gtx/rotate_vector.hpp>

class GameObject 
{
protected:
	unsigned int base;
public:
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 heading = glm::vec3(0.0, 0.0, -1.0);  ///<Current heading (direction) the GameObject is facing.
	GameObject(glm::vec3 pos);
	~GameObject();
	virtual unsigned int setupDrawing(unsigned int listBase);
	virtual void drawScene();
	virtual void start() = 0;
	virtual void update(int deltaTime) = 0;
	static std::map <int, bool> GameObject::specialKeys;
	static std::map <char, bool> GameObject::keys;
	static bool debugMode;

	float size = 1.0;

	bool active = true;

	Collider* collider = NULL;
	Color color = { 1.0f, 1.0f, 1.0f, 1.0f };

	Texture* texture = NULL;

	float momentum = 0.0f;

	/*float momentumX = 0.0f, momentumY = 0.0f, momentumZ = 0.0f;*/

	virtual void collides(GameObject* other);
};

