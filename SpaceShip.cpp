#include "SpaceShip.h"

SpaceShip::SpaceShip(glm::vec3 pos, Color col) : GameObject(position)
{
	this->position = pos;
	this->color = col;
	//SpaceShip::collider = new CubeCollider (&this->position, 1.5, 1.5, 1.5);
	SpaceShip::collider = new SphereCollider(&this->position, 20, .75, .75, .75);
}


SpaceShip::~SpaceShip()
{
	delete SpaceShip::collider;
	SpaceShip::collider = NULL;
}

void SpaceShip::drawScene()
{
	float lightPos[] = { 1.0, 2.0, 0.0, 1.0 };
	//float lightAmb[] = { 0.2, 0.2, 0.2, 1.0 };
	//float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	//float spotExponent = 2.0f;

	//glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);
	//glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);
	glPushMatrix();
	glTranslatef(this->position.x, this->position.y, this->position.z);
	glRotatef(pitchAngle, 0.0, 0.0, 1.0);
	glRotatef(rotationAngle, 0.0, 1.0, 0.0);
	glCallList(this->base); // Draw SpaceShip.
	//float matAmb[] = { this->color.red / 255, this->color.green / 255, this->color.blue / 255, 1.0 };
	//float matDif[] = { this->color.red / 255, this->color.green / 255, this->color.blue / 255, 1.0 };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);
	glPopMatrix();

	glPushMatrix();
	float spotDirection[] = { this->heading.x, this->heading.y, this->heading.z };
	lightPos[0] = this->position.x - this->heading.x, lightPos[1] = this->position.y - this->heading.y, lightPos[2] = this->position.z - this->heading.z;
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDirection);
	glPopMatrix();

	//Drawing GUI
	if (activeUI) {

		drawUI();
	}

	if (debugMode) {
		this->collider->Draw();
	}
}

void SpaceShip::start()
{

}

void SpaceShip::update(int deltaTime)
{
	float moveStep = velocity * (deltaTime / 1000.0); //movement speed in units per second * deltaTime in sec = moveStep
	float turningSpeed = turnSpeed * (deltaTime / 1000.0); //turning speed (degrees/sec) * deltaTime in sec = turning speed over delta time
	
	velocity = (forwardAcc - backwardAcc) / mass;
	turnSpeed = leftTurnSpeed - rightTurnSpeed;
	this->position += this->heading * moveStep;
	this->rotationAngle += turningSpeed;
	this->momentum = glm::abs(velocity) * this->mass;

	if (velocity > 0 && velocity < 0.1) {
		velocity = 0.0;
	}

	if (velocity > 0.0) {
		velocity -= 0.1f;
		forwardAcc -= 0.1f;
	}
	if (velocity < 0.0) {
		velocity += 0.1f;
		backwardAcc -= 0.1f;
	}

	if (turnSpeed > 0) {
		turnSpeed -= 0.75f;
		leftTurnSpeed -= 0.75f;
	}
	if (turnSpeed < 0) {
		turnSpeed += 0.75f;
		rightTurnSpeed -= 0.75f;
	}

	if (specialKeys[GLUT_KEY_DOWN]) {
		if (forwardAcc > 0) {
			forwardAcc -= 0.2f;
		}
		if (backwardAcc < maxVelocity) {
			backwardAcc += 0.2f;
		}
		/*velocity = (forwardAcc - backwardAcc) / mass;*/
		/*this->position -= this->heading * moveStep;*/
	}

	if (specialKeys[GLUT_KEY_UP]) {
		if (backwardAcc > 0) {
			backwardAcc -= 0.2f;
		}
		if (forwardAcc < maxVelocity) {
			forwardAcc += 0.2f;
		}
		/*velocity = (forwardAcc - backwardAcc)/mass;*/
		/*this->position += this->heading * moveStep;*/
	}

	if (specialKeys[GLUT_KEY_PAGE_UP]) {
		this->pitchAngle += moveStep; //in degrees not radians
	}

	if (specialKeys[GLUT_KEY_PAGE_DOWN]) {
		this->pitchAngle -= moveStep; //in degrees not radians
	}

	if (specialKeys[GLUT_KEY_LEFT]) {
		if (rightTurnSpeed > 0) {
			rightTurnSpeed -= 3.0f;
		}
		if (leftTurnSpeed < maxTurnSpeed) {
			leftTurnSpeed += 3.0f;
		}
		//this->rotationAngle += moveStep; //in degrees not radians
	}

	if (specialKeys[GLUT_KEY_RIGHT]) {
		if (leftTurnSpeed > 0) {
			leftTurnSpeed -= 3.0f;
		}
		if (rightTurnSpeed < maxTurnSpeed) {
			rightTurnSpeed += 3.0f;
		}
		//this->rotationAngle -= moveStep; //in degrees not radians
	}

	this->heading = glm::rotate(this->startingHeading, glm::radians(rotationAngle), glm::vec3(0.0, 1.0, 0.0));
	this->heading = glm::rotate(this->heading, glm::radians(pitchAngle), glm::vec3(0, 0, 1));
}

unsigned int SpaceShip::setupDrawing(unsigned int baseList)
{
	for (int i = 0; i < 4 * UIimage->sizeY * UIimage->sizeX; i += 4) {
		if (
			UIimage->data[i] < 10 &&
			UIimage->data[i + 1] >= 235 &&
			UIimage->data[i + 2] >= 235
			) {
			UIimage->data[i + 3] = 0x00;
		}
	}

	float spotExponent = 30.0f;
	float spotAngle = 55.0f;

	float matAmb[] = { this->color.red / 255, this->color.green / 255, this->color.blue / 255, 1.0 };
	glGenTextures(4, _texture);
	LoadAllTextures();

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.005);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.005);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotAngle);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, spotExponent);

	this->base = ++baseList;
	glNewList(this->base, GL_COMPILE);
	glColor4f(this->color.red, this->color.green, this->color.blue, this->color.alpha);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matAmb);

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, _texture[1]);
	glBegin(GL_QUADS);

	//Body - Top
	glTexCoord2f(this->position.x + .5, this->position.z + .75); glNormal3f(0, 1, 0); glVertex3f(this->position.x + .5, this->position.y + 0.55, this->position.z + .75);
	glTexCoord2f(this->position.x + .5, this->position.z - .75); glNormal3f(0, 1, 0); glVertex3f(this->position.x + .5, this->position.y + 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x - .5, this->position.z - .75); glNormal3f(0, 1, 0); glVertex3f(this->position.x - .5, this->position.y + 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x - .5, this->position.z + .75); glNormal3f(0, 1, 0); glVertex3f(this->position.x - .5, this->position.y + 0.55, this->position.z + .75);

	//Body - Bottom
	glTexCoord2f(this->position.x - .5, this->position.z + .75); glVertex3f(this->position.x - .5, this->position.y - 0.55, this->position.z + .75);
	glTexCoord2f(this->position.x - .5, this->position.z - .75); glVertex3f(this->position.x - .5, this->position.y - 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x + .5, this->position.z - .75); glVertex3f(this->position.x + .5, this->position.y - 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x + .5, this->position.z + .75); glVertex3f(this->position.x + .5, this->position.y - 0.55, this->position.z + .75);

	//Front - top
	/*glTexCoord2f(this->position.x - .5, this->position.z - 1.5); glVertex3f(this->position.x - .5, this->position.y, this->position.z - 1.5);
	glTexCoord2f(this->position.x - .5, this->position.z - .75); glVertex3f(this->position.x - .5, this->position.y + 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x + .5, this->position.z - .75); glVertex3f(this->position.x + .5, this->position.y + 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x + .5, this->position.z - 1.5); glVertex3f(this->position.x + .5, this->position.y, this->position.z - 1.5);*/

	//Front - bottom
	glTexCoord2f(this->position.x + .5, this->position.z - 1.5);glTexCoord2f(this->position.x - .5, this->position.z - .75); glVertex3f(this->position.x - .5, this->position.y - 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x - .5, this->position.z - 1.5); glVertex3f(this->position.x - .5, this->position.y, this->position.z - 1.5);
	glTexCoord2f(this->position.x + .5, this->position.z - 1.5); glVertex3f(this->position.x + .5, this->position.y, this->position.z - 1.5);
	glTexCoord2f(this->position.x + .5, this->position.z - .75); glVertex3f(this->position.x + .5, this->position.y - 0.55, this->position.z - .75);

	//Front left - top
	/*glTexCoord2f(this->position.x - 1, this->position.z - 1); glVertex3f(this->position.x - 1, this->position.y, this->position.z - 1);
	glTexCoord2f(this->position.x - 1, this->position.z - .325); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z - .325);
	glTexCoord2f(this->position.x - .5, this->position.z - .75); glVertex3f(this->position.x - .5, this->position.y + 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x - .5, this->position.z - 1.5); glVertex3f(this->position.x - .5, this->position.y, this->position.z - 1.5);*/

	//Front left - bot
	glTexCoord2f(this->position.x - .5, this->position.z - 1.5); glVertex3f(this->position.x - .5, this->position.y, this->position.z - 1.5);
	glTexCoord2f(this->position.x - .5, this->position.z - .75); glVertex3f(this->position.x - .5, this->position.y - 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x - 1, this->position.z - .325); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z - .325);
	glTexCoord2f(this->position.x - 1, this->position.z - 1); glVertex3f(this->position.x - 1, this->position.y, this->position.z - 1);

	//Front right - top
	/*glTexCoord2f(this->position.x + .5, this->position.z - 1.5); glVertex3f(this->position.x + .5, this->position.y, this->position.z - 1.5);
	glTexCoord2f(this->position.x + .5, this->position.z - .75); glVertex3f(this->position.x + .5, this->position.y + 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x + 1, this->position.z - .325); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z - .325);
	glTexCoord2f(this->position.x + 1, this->position.z - 1); glVertex3f(this->position.x + 1, this->position.y, this->position.z - 1);*/

	//Front right - bot
	glTexCoord2f(this->position.x + 1, this->position.z - 1); glVertex3f(this->position.x + 1, this->position.y, this->position.z - 1);
	glTexCoord2f(this->position.x + 1, this->position.z - .325); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z - .325);
	glTexCoord2f(this->position.x + .5, this->position.z - .75); glVertex3f(this->position.x + .5, this->position.y - 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x + .5, this->position.z - 1.5); glVertex3f(this->position.x + .5, this->position.y, this->position.z - 1.5);

	//Right wing - Top
	glTexCoord2f(this->position.x + 1, this->position.z + 1); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x + 1, this->position.z - .325); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z - .325);
	glTexCoord2f(this->position.x + .5, this->position.z - .75); glVertex3f(this->position.x + .5, this->position.y + 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x + .5, this->position.z + .75); glVertex3f(this->position.x + .5, this->position.y + 0.55, this->position.z + .75);

	//Left wing - Top
	glTexCoord2f(this->position.x - .5, this->position.z + .75); glVertex3f(this->position.x - .5, this->position.y + 0.55, this->position.z + .75);
	glTexCoord2f(this->position.x - .5, this->position.z - .75); glVertex3f(this->position.x - .5, this->position.y + 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x - 1, this->position.z - .325); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z - .325);
	glTexCoord2f(this->position.x - 1, this->position.z + 1); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z + 1);

	//Left wing edge - top
	glTexCoord2f(this->position.x - 1.25, this->position.z - .75); glVertex3f(this->position.x - 1.25, this->position.y, this->position.z - .75);
	glTexCoord2f(this->position.x - 1.5, this->position.z); glVertex3f(this->position.x - 1.5, this->position.y, this->position.z);
	glTexCoord2f(this->position.x - 1, this->position.z - 0.325); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z - 0.325);
	glTexCoord2f(this->position.x - 1, this->position.z - 1); glVertex3f(this->position.x - 1, this->position.y, this->position.z - 1);

	//Left wing edge - bot
	glTexCoord2f(this->position.x - 1, this->position.z - 1); glVertex3f(this->position.x - 1, this->position.y, this->position.z - 1);
	glTexCoord2f(this->position.x - 1, this->position.z - 0.325); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z - 0.325);
	glTexCoord2f(this->position.x - 1.5, this->position.z); glVertex3f(this->position.x - 1.5, this->position.y, this->position.z);
	glTexCoord2f(this->position.x - 1.25, this->position.z - .75); glVertex3f(this->position.x - 1.25, this->position.y, this->position.z - .75);

	//Right wing edge - top
	glTexCoord2f(this->position.x + 1, this->position.z - 1); glVertex3f(this->position.x + 1, this->position.y, this->position.z - 1);
	glTexCoord2f(this->position.x + 1, this->position.z - 0.325); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z - 0.325);
	glTexCoord2f(this->position.x + 1.5, this->position.z); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z);
	glTexCoord2f(this->position.x + 1.25, this->position.z - .75); glVertex3f(this->position.x + 1.25, this->position.y, this->position.z - .75);

	//Right wing edge - bot
	glTexCoord2f(this->position.x + 1.25, this->position.z - .75); glVertex3f(this->position.x + 1.25, this->position.y, this->position.z - .75);
	glTexCoord2f(this->position.x + 1.5, this->position.z); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z);
	glTexCoord2f(this->position.x + 1, this->position.z - .325); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z - 0.325);
	glTexCoord2f(this->position.x + 1, this->position.z - 1); glVertex3f(this->position.x + 1, this->position.y, this->position.z - 1);

	//Left wing - Bottom
	glTexCoord2f(this->position.x - 1, this->position.z + 1); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x - 1, this->position.z - .325); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z - .325);
	glTexCoord2f(this->position.x - .5, this->position.z - .75); glVertex3f(this->position.x - .5, this->position.y - 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x - .5, this->position.z + .75); glVertex3f(this->position.x - .5, this->position.y - 0.55, this->position.z + .75);

	//Right wing - Bottom
	glTexCoord2f(this->position.x + .5, this->position.z + .75); glVertex3f(this->position.x + .5, this->position.y - 0.55, this->position.z + .75);
	glTexCoord2f(this->position.x + .5, this->position.z - .75); glVertex3f(this->position.x + .5, this->position.y - 0.55, this->position.z - .75);
	glTexCoord2f(this->position.x + 1, this->position.z - .325); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z - .325);
	glTexCoord2f(this->position.x + 1, this->position.z + 1); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z + 1);
	
	//Right wing - Tip
	glTexCoord2f(this->position.x + 1.5, this->position.z + 1.5); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x + 1.5, this->position.z); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z);
	glTexCoord2f(this->position.x + 1, this->position.z - .325); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z - .325);
	glTexCoord2f(this->position.x + 1, this->position.z + 1); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z + 1);

	//Left wing - Tip
	glTexCoord2f(this->position.x - 1, this->position.z + 1); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x - 1, this->position.z - .325); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z - .325);
	glTexCoord2f(this->position.x - 1.5, this->position.z); glVertex3f(this->position.x - 1.5, this->position.y, this->position.z);
	glTexCoord2f(this->position.x - 1.5, this->position.z + 1.5); glVertex3f(this->position.x - 1.5, this->position.y, this->position.z + 1.5);

	//Right wing - Tip Bottom
	glTexCoord2f(this->position.x + 1, this->position.z + 1); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x + 1, this->position.z - .325); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z - .325);
	glTexCoord2f(this->position.x + 1.5, this->position.z); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z);
	glTexCoord2f(this->position.x + 1.5, this->position.z + 1.5); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z + 1.5);

	//Left wing - Tip Bottom
	glTexCoord2f(this->position.x - 1.5, this->position.z + 1.5); glVertex3f(this->position.x - 1.5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x - 1.5, this->position.z); glVertex3f(this->position.x - 1.5, this->position.y, this->position.z);
	glTexCoord2f(this->position.x - 1, this->position.z - .325); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z - .325);
	glTexCoord2f(this->position.x - 1, this->position.z + 1); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z + 1);

	//Lower back body - bot
	glTexCoord2f(this->position.x + .5, this->position.z + .75); glVertex3f(this->position.x + .5, this->position.y - 0.55, this->position.z + .75);
	glTexCoord2f(this->position.x + .25, this->position.z + 1.5); glVertex3f(this->position.x + .25, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x - .25, this->position.z + 1.5); glVertex3f(this->position.x - .25, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x - .5, this->position.z + .75); glVertex3f(this->position.x - .5, this->position.y - 0.55, this->position.z + .75);

	//Upper back body - top
	glTexCoord2f(this->position.x + .25, this->position.z + 1.5); glVertex3f(this->position.x + .25, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x + .5, this->position.z + .75); glVertex3f(this->position.x + .5, this->position.y + 0.55, this->position.z + .75);
	glTexCoord2f(this->position.x - .5, this->position.z + .75); glVertex3f(this->position.x - .5, this->position.y + 0.55, this->position.z + .75);
	glTexCoord2f(this->position.x - .25, this->position.z + 1.5); glVertex3f(this->position.x - .25, this->position.y, this->position.z + 1.5);

	//Back body - left top
	glTexCoord2f(this->position.x - .25, this->position.z + 1.5); glVertex3f(this->position.x - .25, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x - .5, this->position.z + .75); glVertex3f(this->position.x - .5, this->position.y + 0.55, this->position.z + .75);
	glTexCoord2f(this->position.x - 1, this->position.z + 1); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x - .5, this->position.z + 1.5); glVertex3f(this->position.x - .5, this->position.y, this->position.z + 1.5);

	//Back body - right top
	glTexCoord2f(this->position.x + .5, this->position.z + 1.5); glVertex3f(this->position.x + .5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x + 1, this->position.z + 1); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x + .5, this->position.z + .75); glVertex3f(this->position.x + .5, this->position.y + 0.55, this->position.z + .75);
	glTexCoord2f(this->position.x + .25, this->position.z + 1.5); glVertex3f(this->position.x + .25, this->position.y, this->position.z + 1.5);

	//Back body - right bot
	glTexCoord2f(this->position.x + 1, this->position.z + 1); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x + .5, this->position.z + 1.5); glVertex3f(this->position.x + .5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x + .25, this->position.z + 1.5); glVertex3f(this->position.x + .25, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x + .5, this->position.z + .75); glVertex3f(this->position.x + .5, this->position.y - 0.55, this->position.z + .75);

	//Back body - left bot
	glTexCoord2f(this->position.x - .5, this->position.z + .75); glVertex3f(this->position.x - .5, this->position.y - 0.55, this->position.z + .75);
	glTexCoord2f(this->position.x - .25, this->position.z + 1.5); glVertex3f(this->position.x - .25, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x - .5, this->position.z + 1.5); glVertex3f(this->position.x - .5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x - 1, this->position.z + 1); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z + 1);
	
	//Back body - middle collapse left
	/*glTexCoord2f(this->position.x - 1, this->position.z + 1); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x - .5, this->position.z + 1.5); glVertex3f(this->position.x - .5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x - 1, this->position.z + 1); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x - 1.25, this->position.z + .5); glVertex3f(this->position.x - 1.25, this->position.y , this->position.z + .5);

	glTexCoord2f(this->position.x - 1.25, this->position.z + .5); glVertex3f(this->position.x - 1.25, this->position.y, this->position.z + .5);
	glTexCoord2f(this->position.x - 1, this->position.z + 1); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x - 1.5, this->position.z + 1.5); glVertex3f(this->position.x - 1.5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x - 1, this->position.z + 1); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z + 1);*/

	//Back body - middle collapse right
	/*glTexCoord2f(this->position.x + 1.25, this->position.z + .5); glVertex3f(this->position.x + 1.25, this->position.y, this->position.z + .5);
	glTexCoord2f(this->position.x + 1, this->position.z + 1); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x + .5, this->position.z + 1.5); glVertex3f(this->position.x + .5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x + 1, this->position.z + 1); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z + 1);

	glTexCoord2f(this->position.x + 1, this->position.z + 1); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x + 1.5, this->position.z + 1.5); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x + 1, this->position.z + 1); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x + 1.25, this->position.z + .5); glVertex3f(this->position.x + 1.25, this->position.y, this->position.z + .5);*/

	glTexCoord2f(this->position.x - .5, this->position.y); glVertex3f(this->position.x - .5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x - 1, this->position.y + 0.35); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x - 1.5, this->position.y); glVertex3f(this->position.x - 1.5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x - 1, this->position.y); glVertex3f(this->position.x - 1, this->position.y, this->position.z + .75);

	glTexCoord2f(this->position.x - .5, this->position.y); glVertex3f(this->position.x - .5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x - 1, this->position.y); glVertex3f(this->position.x - 1, this->position.y, this->position.z + .75);
	glTexCoord2f(this->position.x - 1.5, this->position.y); glVertex3f(this->position.x - 1.5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x - 1, this->position.y - 0.35); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z + 1);

	glTexCoord2f(this->position.x + 1.5, this->position.y); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x + 1, this->position.y + 0.35); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z + 1);
	glTexCoord2f(this->position.x + .5, this->position.y); glVertex3f(this->position.x + .5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x + 1, this->position.y); glVertex3f(this->position.x + 1, this->position.y, this->position.z + .75);

	glTexCoord2f(this->position.x + 1.5, this->position.y); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x + 1, this->position.y); glVertex3f(this->position.x + 1, this->position.y, this->position.z + .75);
	glTexCoord2f(this->position.x + .5, this->position.y + 0.35); glVertex3f(this->position.x + .5, this->position.y, this->position.z + 1.5);
	glTexCoord2f(this->position.x + 1, this->position.y - 0.35); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z + 1);

	glEnd();

	glBindTexture(GL_TEXTURE_2D, _texture[2]);
	glDisable(GL_LIGHTING);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex3f(this->position.x + .5, this->position.y, this->position.z - 1.5);
	glTexCoord2f(0, 1); glVertex3f(this->position.x + .5, this->position.y + 0.55, this->position.z - .75);
	glTexCoord2f(1, 1); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z - .325);
	glTexCoord2f(1, 0); glVertex3f(this->position.x + 1, this->position.y, this->position.z - 1);

	glTexCoord2f(0, 0); glVertex3f(this->position.x - 1, this->position.y, this->position.z - 1);
	glTexCoord2f(0, 1); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z - .325);
	glTexCoord2f(1, 1); glVertex3f(this->position.x - .5, this->position.y + 0.55, this->position.z - .75);
	glTexCoord2f(1, 0); glVertex3f(this->position.x - .5, this->position.y, this->position.z - 1.5);

	//Front - top
	glTexCoord2f(0, 0); glVertex3f(this->position.x - .5, this->position.y, this->position.z - 1.5);
	glTexCoord2f(0, 1); glVertex3f(this->position.x - .5, this->position.y + 0.55, this->position.z - .75);
	glTexCoord2f(1, 1); glVertex3f(this->position.x + .5, this->position.y + 0.55, this->position.z - .75);
	glTexCoord2f(1, 0); glVertex3f(this->position.x + .5, this->position.y, this->position.z - 1.5);

	glEnd();
	glEnable(GL_LIGHTING);
	glPopMatrix();
	//glBindTexture(GL_TEXTURE_2D, _texture[3]);
	//glBegin(GL_QUADS);
	//glDisable(GL_LIGHTING);
	////Back body - middle collapse left
	////glTexCoord2f(0, 0); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z + 1);
	////glTexCoord2f(0, 1); glVertex3f(this->position.x - .5, this->position.y, this->position.z + 1.5);
	////glTexCoord2f(1, 1); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z + 1);
	////glTexCoord2f(1, 0); glVertex3f(this->position.x - 1.25, this->position.y , this->position.z + .5);

	////glTexCoord2f(0, 0); glVertex3f(this->position.x - 1.25, this->position.y, this->position.z + .5);
	////glTexCoord2f(0, 1); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z + 1);
	////glTexCoord2f(1, 1); glVertex3f(this->position.x - 1.5, this->position.y, this->position.z + 1.5);
	////glTexCoord2f(1, 0); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z + 1);

	////Back body - middle collapse right
	//glTexCoord2f(this->position.x + 1.5, this->position.y); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z + 1.5);
	//glTexCoord2f(this->position.x + 1, this->position.y + 0.35); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z + 1);
	//glTexCoord2f(this->position.x + .5, this->position.y); glVertex3f(this->position.x + .5, this->position.y, this->position.z + 1.5);
	//glTexCoord2f(this->position.x + 1, this->position.y); glVertex3f(this->position.x + 1, this->position.y, this->position.z + .75);

	//glTexCoord2f(this->position.x + 1.5, this->position.y); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z + 1.5);
	//glTexCoord2f(this->position.x + 1, this->position.y); glVertex3f(this->position.x + 1, this->position.y, this->position.z + .75);
	//glTexCoord2f(this->position.x + .5, this->position.y + 0.35); glVertex3f(this->position.x + .5, this->position.y, this->position.z + 1.5);
	//glTexCoord2f(this->position.x + 1, this->position.y - 0.35); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z + 1);

	////Back body - middle collapse left
	//glTexCoord2f(this->position.x - .5, this->position.y); glVertex3f(this->position.x - .5, this->position.y, this->position.z + 1.5);
	//glTexCoord2f(this->position.x - 1, this->position.y + 0.35); glVertex3f(this->position.x - 1, this->position.y + 0.35, this->position.z + 1);
	//glTexCoord2f(this->position.x - 1.5, this->position.y); glVertex3f(this->position.x - 1.5, this->position.y, this->position.z + 1.5);
	//glTexCoord2f(this->position.x - 1, this->position.y); glVertex3f(this->position.x - 1, this->position.y, this->position.z + .75);

	//glTexCoord2f(this->position.x - .5, this->position.y); glVertex3f(this->position.x - .5, this->position.y, this->position.z + 1.5);
	//glTexCoord2f(this->position.x - 1, this->position.y); glVertex3f(this->position.x - 1, this->position.y, this->position.z + .75);
	//glTexCoord2f(this->position.x - 1.5, this->position.y); glVertex3f(this->position.x - 1.5, this->position.y, this->position.z + 1.5);
	//glTexCoord2f(this->position.x - 1, this->position.y - 0.35); glVertex3f(this->position.x - 1, this->position.y - 0.35, this->position.z + 1);

	////glTexCoord2f(this->position.x + 1.5, this->position.y); glVertex3f(this->position.x + 1, this->position.y, this->position.z + .5);
	////glTexCoord2f(this->position.x + 1, this->position.y + 0.35); glVertex3f(this->position.x + .5, this->position.y, this->position.z + 1.5);
	////glTexCoord2f(this->position.x + .5, this->position.y); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z + 1);
	////glTexCoord2f(this->position.x + 1.25, this->position.y); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z + 1.5);

	///*glTexCoord2f(this->position.x + 1.25, this->position.y); glVertex3f(this->position.x + 1.25, this->position.y, this->position.z + .5);
	//glTexCoord2f(this->position.x + .5, this->position.y); glVertex3f(this->position.x + .5, this->position.y, this->position.z + 1.5);
	//glTexCoord2f(this->position.x + 1, this->position.y + 0.35); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z + 1);
	//glTexCoord2f(this->position.x + 1, this->position.y - 0.35); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z + 1);*/

	////glTexCoord2f(0, 0); glVertex3f(this->position.x + 1.25, this->position.y, this->position.z + .5);
	////glTexCoord2f(0, 1); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z + 1);
	////glTexCoord2f(1, 1); glVertex3f(this->position.x + .5, this->position.y, this->position.z + 1.5);
	////glTexCoord2f(1, 0); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z + 1);

	////glTexCoord2f(0, 0); glVertex3f(this->position.x + 1, this->position.y - 0.35, this->position.z + 1);
	////glTexCoord2f(0, 1); glVertex3f(this->position.x + 1.5, this->position.y, this->position.z + 1.5);
	////glTexCoord2f(1, 1); glVertex3f(this->position.x + 1, this->position.y + 0.35, this->position.z + 1);
	////glTexCoord2f(1, 0); glVertex3f(this->position.x + 1.25, this->position.y, this->position.z + .5);

	//glEnable(GL_LIGHTING);
	//glEnd();
	//glPopMatrix();

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	glColor4f(.75, .75, .75, .5);
	glTranslatef(this->position.x + 1, this->position.y + .25, this->position.z - .325);
	glutSolidCylinder(.1, 1.1, 20, 20);
	glTranslatef(this->position.x - 1.5, this->position.y + .25, this->position.z);
	glRotatef(90, 0, 1, 0);
	glutSolidCylinder(.1, 1, 20, 20);
	glTranslatef(this->position.x - 0.70, this->position.y, this->position.z);
	glutSolidCylinder(.1, 1, 20, 20);
	glRotatef(-90, 0, 1, 0);
	glTranslatef(this->position.x - 0.5, this->position.y - .25, this->position.z - .65);
	glutSolidCylinder(.1, 1.1, 20, 20);

	glDisable(GL_LIGHTING);
	glTranslatef(this->position.x , this->position.y - .25, this->position.z + .875);
	glColor4f(1, .65, 0, 1);
	glutSolidCylinder(.225, .5, 6, 6);
	glTranslatef(this->position.x + 2, this->position.y, this->position.z);
	glutSolidCylinder(.225, .5, 6, 6);

	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	// Specify how texture values combine with current surface color values.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEndList();
	return this->base;

}

void SpaceShip::collides(GameObject* other) {
	if (debugMode) {
		std::cout << "SpaceShip collides!" << std::endl;
	}

	/*velocity -= velocity / 2;*/
	velocity *= -.5;
	forwardAcc *= -1;
	backwardAcc *= -1;
	durability -= other->momentum;
	/*std::cout << this->durability << std::endl;*/
}

void SpaceShip::LoadAllTextures()
{
	glBindTexture(GL_TEXTURE_2D, _texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, UIimage->sizeX, UIimage->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, UIimage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, _texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ShipTextureImage->sizeX, ShipTextureImage->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, ShipTextureImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, _texture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ShipWindowImage->sizeX, ShipWindowImage->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, ShipWindowImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, _texture[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ShipEngineImage->sizeX, ShipEngineImage->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, ShipEngineImage->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void SpaceShip::drawUI()
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glLoadIdentity();
	glColor4f(1, 1, 1, 1);
	glTranslatef(0.0, -1.0, -1.0);

	glBindTexture(GL_TEXTURE_2D, _texture[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-0.6, -1.0, -2);
	glTexCoord2f(1, 0); glVertex3f(0.6, -1.0, -2);
	glTexCoord2f(1, 1); glVertex3f(0.6, -0.6, -2);
	glTexCoord2f(0, 1); glVertex3f(-0.6, -0.6, -2);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_TEXTURE_2D);
	glColor4f(0, .749, 1.0, 1.0);
	playerStats.floatToString(playerStats.theStringBuffer, 5, abs(velocity));
	glRasterPos3f(-0.275, -1.155, -2);
	//glRotatef(0, this->position.y, this->position.z, this->position.z);
	playerStats.writeBitmapString((void*)playerStats.font, "Velocity: ");
	playerStats.writeBitmapString((void*)playerStats.font, playerStats.theStringBuffer);

	playerStats.floatToString(playerStats.theStringBuffer, 5, durability);
	glRasterPos3f(-0.3, -1.275, -2);
	playerStats.writeBitmapString((void*)playerStats.font, "Durability: ");
	playerStats.writeBitmapString((void*)playerStats.font, playerStats.theStringBuffer);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
}



