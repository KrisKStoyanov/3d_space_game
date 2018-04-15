#pragma once
#include "GameObject.h"
//#define TURNING_SPEED 400.0 //<turning speed in degrees per second
//#define MOVE_SPEED 10.0 //<move speed in coordinate units per second

class SpaceShip : public GameObject
{
private:
	int base;
public:
	SpaceShip(glm::vec3 pos, Color col );
	~SpaceShip();
	void drawScene();
	void SpaceShip::start();
	void SpaceShip::update(int deltaTime);
	unsigned int setupDrawing(unsigned int baseList);

	float durability = 100;

	void collides(GameObject* other);

	glm::vec3 startingHeading = heading; ///<Starting facing direction of the spaceship.
	float rotationAngle = 0.0;
	float pitchAngle = 0.0; ///<Rotation and pitch angles for our spaceship

	float velocity = 0.0f;
	float maxVelocity = 30.0f;

	float mass = 1.15f;

	float forwardAcc = 0.0f;
	float backwardAcc = 0.0f;

	//float generalSpeed = 0.0f;
	//float forwardSpeed = 0.0f;
	//float backSpeed = 0.0f;
	//float maxSpeed = 30.0f;

	float turnSpeed = 0.0f;
	float leftTurnSpeed = 0.0f;
	float rightTurnSpeed = 0.0f;
	float maxTurnSpeed = 35.0f;

	Statistics playerStats;
	BitMapFile * UIimage = getbmp("./Resources/gui.bmp");
	BitMapFile * ShipTextureImage = getbmp("./Resources/shipTextures.bmp");
	BitMapFile * ShipWindowImage = getbmp("./Resources/shipWindow.bmp");
	BitMapFile * ShipEngineImage = getbmp("./Resources/shipEngine.bmp");
	unsigned int _texture[4];
	void LoadAllTextures();

	void drawUI();
	bool activeUI = false;
};

