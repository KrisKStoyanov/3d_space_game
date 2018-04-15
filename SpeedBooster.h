#pragma once
#include "GameObject.h"

class SpeedBooster : public GameObject
{
public:
	SpeedBooster(glm::vec3 pos, Color col);
	~SpeedBooster();
	void drawScene();
	void SpeedBooster::start();
	void SpeedBooster::update(int deltaTime);
	unsigned int setupDrawing(unsigned int baseList);
	void collides(GameObject * other);

	float mass = 1.5f;
	float speedX = 0.0f;
	float speedY = 0.0f;
	float speedZ = 0.0f;
}; 

