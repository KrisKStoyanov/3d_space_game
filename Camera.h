#pragma once
#include "GameObject.h"
#include<glm/gtx/rotate_vector.hpp>
class Camera
{
public:
	Camera(glm::vec3 pos);
	~Camera();
	glm::vec3 position = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 heading = glm::vec3(0.0, 0.0, -1.0);  ///<Current heading (direction) the GameObject is facing.
	float Xangle = 0.0, Yangle = 0.0, Zangle = 0.0;
	void Follow(GameObject* target, float xDist, float yDist);
	void Rotate(float x, float y, float z);
};

