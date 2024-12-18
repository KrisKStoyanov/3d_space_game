#include "GameEngine.h"

int main(int argc, char **argv) {

	//Initialise the engine.
	GameEngine::initEngine(argc, argv, "Space Racer", true, 1366, 768);

	//Start the game engine.
	GameEngine::startEngine();

	return 0;
}