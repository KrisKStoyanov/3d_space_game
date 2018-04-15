#include "GameEngine.h"
#include <string>

bool GameEngine::debugMode;
std::vector<GameObject*> GameEngine::gameobjects;
GameObject* GameEngine::cameraFollow;
int GameEngine::oldTimeSinceStart;
int GameEngine::newTimeSinceStart;
//std::map <int, bool> GameObject::specialKeys;
//std::map <char, bool> GameObject::keys;
unsigned int GameEngine::base;
Skybox GameEngine::gameSkybox;
Logo GameEngine::gameLogo;
int GameEngine::cameraMode;
Statistics GameEngine::gameStats;
SpaceShip* GameEngine::player;

float GameEngine::fps = 0;
int GameEngine::frameRate = 0;
int GameEngine::frameTime;

void GameEngine::updateGame() {

	if (player->durability <= 0) {
		GameEngine::Restart();
	}
	//std::cout << player->durability << std::endl;
	//Calculate delta time (in mili seconds).
	oldTimeSinceStart = newTimeSinceStart;
	newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	int deltaTime = newTimeSinceStart - oldTimeSinceStart;

	GameEngine::frameRate++;
	if (GameEngine::newTimeSinceStart - GameEngine::frameTime > 200) {
		fps = GameEngine::frameRate * 1000.0 / (GameEngine::newTimeSinceStart - GameEngine::frameTime);
		frameTime = newTimeSinceStart;
		GameEngine::frameRate = 0;
	}

	//If the last frame was rendered less than 1 ms ago, the detalaTime will be 0 ms. This causes problems in calculations, so sleep for 1ms to adjust.
	if (deltaTime == 0) {
		Sleep(1);
		newTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
		deltaTime = newTimeSinceStart - oldTimeSinceStart;
	}

	//Run update for all game objects.
	for (std::vector<GameObject*>::size_type i = 0; i != gameobjects.size(); i++) {
		gameobjects[i]->update(deltaTime);
	}

	for (std::vector<GameObject*>::size_type i = 0; i != gameobjects.size(); i++) {
		for (std::vector<GameObject*>::size_type j = i + 1; j != gameobjects.size(); j++) {
			if (gameobjects[i]->collider != NULL) {
				if (gameobjects[i]->collider->collidesWith(gameobjects[j]->collider)) {
					gameobjects[i]->collides(gameobjects[j]);
					gameobjects[j]->collides(gameobjects[i]);
				}
			}
		}
	}

	//Done so indicate that it's time to redraw.
	glutPostRedisplay();
}

GameEngine::GameEngine()
{
}


GameEngine::~GameEngine()
{
}

void GameEngine::initEngine(int argc, char **argv, const char* windowTitle, bool debug, int width, int height) {
	GameEngine::debugMode = debug;
	GameObject::debugMode = GameEngine::debugMode;
	//Init glut.
	glutInit(&argc, argv);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(windowTitle);
	glutFullScreen();
	
	//Lambda function defined inside the glutDisplayFunc call to call all relevant drawscenes.
	glutDisplayFunc(displayFunc);

	//Lambda function defined inside glutReshapeFunc to do resize logic.
	glutReshapeFunc(reshapeFunc);

	gameLogo.setup();
	gameSkybox.setup();

	/*glutReshapeFunc([](int w, int h) {
		reshapeFunc(w,h);
	});*/

	//Lambda functions to link our code to glut's keydown andkeyup. Our function deals with both regular and special keys in one.
	glutKeyboardFunc([](unsigned char key, int x, int y) {
		GameObject::keys[key] = true;
		GameEngine::gameLogo.active = false;
		GameEngine::player->activeUI = true;
		//if we press escape, exit the game
		if (key == 27) {
			cleanup();
			exit(0);
		}

		switch (key) {

		case '1':
			cameraMode = 0;
			break;
		case '2':
			cameraMode = 1;
			break;
		case '3':
			cameraMode = 2;
			break;
		case '4':
			cameraMode = 3;
			break;
		case '5':
			cameraMode = 4;
			break;
		case 'r':
			GameEngine::Restart();
			break;
		}
	});

	glutKeyboardUpFunc([](unsigned char key, int x, int y) {
		GameObject::keys[key] = false;
	});

	glutSpecialFunc([](int key, int x, int y) {
		GameObject::specialKeys[key] = true;
		GameEngine::gameLogo.active = false;
		GameEngine::player->activeUI = true;
	});

	glutSpecialUpFunc([](int key, int x, int y) {
		GameObject::specialKeys[key] = false;
	});

	glutIdleFunc(updateGame);

	glewExperimental = GL_TRUE;
	glewInit();

}
 void GameEngine::displayFunc() {
	//Prepare for drawing all objects.
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	float globAmb[] = { 0.05, 0.05, 0.05, 1.0 };
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	
	glEnable(GL_ALPHA_TEST); // Enable alpha
	glEnable(GL_BLEND); // Blending the color from behing with the color of the object
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glAlphaFunc(GL_GREATER, 0.1);

	//Antialiasing testing
	glEnable(GL_POLYGON_SMOOTH);

    glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);// Enable local viewpoint.
	glLightModeli(GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR);
	//glLoadIdentity();
	//If we have no object to follow just put the cam in a static position.
	if (cameraFollow != NULL) {
		//Hardcoded camera variables for the distance bewteen camera and object and y axis distance between camera and object.
		GameEngine::switchCamera(cameraMode);
	}

	//Call drawscene for all gameobjects.
	for (std::vector<GameObject*>::size_type i = 0; i != gameobjects.size(); i++) {
		gameobjects[i]->drawScene();
	}
	//gluLookAt(0, 0, -10, 0, 0, 0, 0, 1, 0);
	glPushMatrix();
	if (gameLogo.active) {
		gameLogo.drawScene();
	}
	gameSkybox.drawScene(cameraFollow->position, 4000);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);

	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	gameStats.floatToString(gameStats.theStringBuffer, 5, fps);
	glRasterPos3f(-.2, 1.25,-2.0);
	gameStats.writeBitmapString((void*)gameStats.font, "FPS: ");
	gameStats.writeBitmapString((void*)gameStats.font, gameStats.theStringBuffer);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glutSwapBuffers(); //Finish Draw Scene.
}

void GameEngine::reshapeFunc(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (float)w / (float)h, 1.0, 8000.0);
	glMatrixMode(GL_MODELVIEW);
	
};

void GameEngine::addGameObject(GameObject* gameobject, bool camFollow) {
	gameobjects.push_back(gameobject);
	if (camFollow) {
		cameraFollow = gameobject;
	}

	base = glGenLists(1);
	base = gameobject->setupDrawing(base);
	gameobject->start();	
}

void GameEngine::startEngine() {
	//Explain main interaction with scene.
	std::cout << "Press escape to exit." << std::endl;

	int distBetween = 8;
	int innerR = 24;
	int outerR = 36;
	float angle = 0.0;

	GameEngine::addGameObject(new Planet(glm::vec3(-60.0, -25, -150.0), { 0.72f, 0.525f, 0.04f, 1.0f }, -66.0f, 15.0f, 22.5f), false);

	GameEngine::addGameObject(new Planet(glm::vec3(90, 25, -180), { 0.95f, 0.64f, 0.37f, 1.0f }, 75, 22.5f,33.75), false);

	//First half circle
	for (int i = 0; i < 8; i++) {
		GameEngine::addGameObject(new Asteroid(glm::vec3(-20.0f + innerR * cos(angle), 0.0, -20.0f + innerR * sin(angle)), { 0.55f, 0.27f, 0.07f, 1.0f }, 1.0f), false);
		angle += 2 * PI / 16;
	}
	angle = 0.0f;
	for (int i = 0; i < 10; i++) {
		GameEngine::addGameObject(new Asteroid(glm::vec3(-20.0f + outerR * cos(angle), 0.0, -20.0f + outerR * sin(angle)), { 0.55f, 0.27f, 0.07f, 1.0f }, 1.0f), false);
		angle += 2 * PI / 20;
	}

	//Left circle extensions
	for (int i = 0; i < 5; i++) {
		GameEngine::addGameObject(new Asteroid(glm::vec3(-44.0f, 0.0, -14.0f - distBetween), { 0.55f, 0.27f, 0.07f, 1.0f }, 1.0f), false);
		distBetween += 8;
	}
	distBetween = 10.0;
	for (int i = 0; i < 5; i++) {
		GameEngine::addGameObject(new Asteroid(glm::vec3(-56.0f, 0.0, -14.0f - distBetween), { 0.55f, 0.27f, 0.07f, 1.0f }, 1.0f), false);
		distBetween += 8;
	}

	//Second half circle
	angle = 0.0f;
	for (int i = 0; i < 8; i++) {
		GameEngine::addGameObject(new Asteroid(glm::vec3(-20.0f + innerR * cos(angle), 0.0, -60.0f + innerR * sin(angle)), { 0.55f, 0.27f, 0.07f, 1.0f }, 1.0f), false);
		angle -= 2 * PI / 16;
	}
	angle = 0.0f;
	for (int i = 0; i < 10; i++) {
		GameEngine::addGameObject(new Asteroid(glm::vec3(-20.0f + outerR * cos(angle), 0.0, -60.0f + outerR * sin(angle)), { 0.55f, 0.27f, 0.07f, 1.0f }, 1.0f), false);
		angle -= 2 * PI / 20;
	}

	//Right circle extensions
	distBetween = 8;
	for (int i = 0; i < 5; i++) {
		GameEngine::addGameObject(new Asteroid(glm::vec3(4.0f, 0.0, -24.0f - distBetween), { 0.55f, 0.27f, 0.07f, 1.0f }, 1.0f), false);
		distBetween += 8;
	}
	distBetween = 8;
	for (int i = 0; i < 5; i++) {
		GameEngine::addGameObject(new Asteroid(glm::vec3(16.0f, 0.0, -24.0f - distBetween), { 0.55f, 0.27f, 0.07f, 1.0f }, 1.0f), false);
		distBetween += 8;
	}

	//Add a movable ship.
	GameEngine::addGameObject(player = new SpaceShip(glm::vec3(0.0, 0.0, 0.0), { 1.0f, 1.0f, 1.0f, 1.0f }), true);

	GameEngine::addGameObject(new Billboard(glm::vec3(80 , 20,- 140), cameraFollow, 1191,  670, "./Resources/spaceShip.bmp" ), false);

	GameEngine::addGameObject(new Billboard(glm::vec3(-100, -10, -130), cameraFollow, 1191, 670, "./Resources/spaceShip.bmp"), false);

	GameEngine::addGameObject(new Star(glm::vec3(-100, -250, -400.0), { 1.0f, 1.0f, 0.0f, 1.0f }, 10.0f), false);


	//Start game loop.

	glutMainLoop();
}

void GameEngine::cleanup() {
	for (auto it = gameobjects.begin(); it != gameobjects.end(); ++it) {
		delete *it;
	}
	gameobjects.clear();
}

void GameEngine::switchCamera(float cameraMode)

{
	float distance = 6;
	float yAm = 3.5f;
	if (cameraMode == 0) {
		gluLookAt(cameraFollow->position.x - (cameraFollow->heading.x * distance), cameraFollow->position.y - (cameraFollow->heading.y * distance), cameraFollow->position.z - (cameraFollow->heading.z * distance),
			cameraFollow->position.x, cameraFollow->position.y, cameraFollow->position.z,
			0.0, 1.0, 0.0);
	}
	else if (cameraMode == 1) {
		gluLookAt(cameraFollow->position.x - (cameraFollow->heading.x * distance), cameraFollow->position.y - (cameraFollow->heading.y * distance) + yAm, cameraFollow->position.z - (cameraFollow->heading.z * distance),
			cameraFollow->position.x, cameraFollow->position.y, cameraFollow->position.z,
			0.0, 1.0, 0.0);
	}
	else if (cameraMode == 2) {
		gluLookAt(cameraFollow->position.x - (cameraFollow->heading.x * distance), cameraFollow->position.y - (cameraFollow->heading.y * distance) + yAm * 8, cameraFollow->position.z - (cameraFollow->heading.z * distance),
			cameraFollow->position.x - 2.0f, cameraFollow->position.y - 2.0f, cameraFollow->position.z - 2.0f,
			0.0, 1.0, 0.0);
	}
	else if (cameraMode == 3){
		gluLookAt(0, 10, -5,
			cameraFollow->position.x, cameraFollow->position.y, cameraFollow->position.z,
			0.0, 1.0, 0.0);
	}
	else {
		gluLookAt(cameraFollow->position.x, cameraFollow->position.y, cameraFollow->position.z,
			cameraFollow->position.x + (cameraFollow->heading.x * distance), cameraFollow->position.y + (cameraFollow->heading.y * distance), cameraFollow->position.z + (cameraFollow->heading.z * distance),
			0.0, 1.0, 0.0);
	}
}


void GameEngine::Restart()
{
	GameEngine::cleanup();
	GameEngine::player->activeUI = false;
	GameEngine::player->heading = glm::vec3(0.0, 0.0, -1.0);
	GameEngine::player->startingHeading = glm::vec3(0.0, 0.0, -1.0);
	GameEngine::cameraMode = 0;
	GameEngine::gameLogo.active = true;
	GameEngine::startEngine();
}



