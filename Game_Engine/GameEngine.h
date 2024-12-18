#pragma once
#include "GameObject.h"
#include "Skybox.h"
#include "Logo.h"

#include "SpaceShip.h"
#include "Asteroid.h"
#include "Planet.h"
#include "Star.h"
#include "Billboard.h"

#include <vector>

class GameEngine
{
private:
	static std::vector<GameObject*> gameobjects; ///<Vector of (pointers to) game objects: all the objects in the game.
	static void updateGame(); ///<Function that updates the game state
	static int oldTimeSinceStart; ///<The old time since the start of the game (from previous frame) for delta tikme calculation.
	static int newTimeSinceStart; ///<The time since the start of the game  for delta tikme calculation.
	static unsigned int base; // Generate display list base. 
public:
	static GameObject* cameraFollow;
	GameEngine();
	~GameEngine();
    static void initEngine(int argc, char **argv, const char* windowTitle = "New Game", bool debugMode = false, int width = 500, int height = 500);
	static void displayFunc();
	static void reshapeFunc(int w, int h);
	///<Initialises the engine, initilising glut and OpenGL.
	static void addGameObject(GameObject* gameobject, bool camFollow); ///<Adds a GameObject to the game.
	static void startEngine(); ///<Start the engine (and the main game loop).
	static void cleanup(); ///<Function to clean up and delete any pointers and anything else when the game exists to prevent memory leaks.
	static Skybox gameSkybox;
	static Logo gameLogo;
	static void switchCamera(float cameraMode);
	static int cameraMode;
	static bool debugMode;

	static Statistics gameStats;

	static SpaceShip * player;

	static float fps;
	static int frameTime;
	static int frameRate;

	static void Restart();
};

