#pragma once
#include "GameObject.h"

	class Planet : public GameObject
{
private:
	int base;

public:
	Planet(glm::vec3 pos, Color col, float discAngle, float size, float discSize);
	~Planet();
	void drawScene();
	unsigned int setupDrawing(unsigned int baseList);
	void Planet::start();
	void Planet::update(int deltaTime);
	void collides(GameObject* other);

	float discAngle;
	float discSize;

	float mass = 1.75f;
	float speedX = 0.0f;
	float speedY = 0.0f;
	float speedZ = 0.0f;
};

