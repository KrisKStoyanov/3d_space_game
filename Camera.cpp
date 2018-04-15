#include "Camera.h"



Camera::Camera(glm::vec3 pos)
{
	this->position = pos;
}

Camera::~Camera()
{
}

void Camera::Follow(GameObject* target, float xDist, float yDist)
{
}

void Camera::Rotate(float x, float y, float z)
{

}
