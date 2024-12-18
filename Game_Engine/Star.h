#pragma once
#include "GameObject.h"
#include "SpaceShip.h"

class Star : public GameObject
{
private:
	int base;
public:
	Star(glm::vec3 pos, Color _asteroidColor, float size);
	~Star();
	void drawScene();
	void Star::start();
	void Star::update(int deltaTime);
	unsigned int setupDrawing(unsigned int baseList);
	void collides(GameObject * other);

	float mass = 1.5f;
	float speedX = 0.0f;
	float speedY = 0.0f;
	float speedZ = 0.0f;

	float t = 0.0f;

	float waitTime = 0.0f;
	glm::vec3 orbitVector = { 0,0,0 };
};

