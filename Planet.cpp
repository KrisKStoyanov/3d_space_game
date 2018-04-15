#include "Planet.h"



Planet::Planet(glm::vec3 pos, Color col, float discAngle, float size, float discSize) : GameObject(position)
{
	this->position = pos;
	this->color = col;
	this->discAngle = discAngle;
	this->size = size;
	this->discSize = discSize;
	//Planet::collider = new CubeCollider(&this->position, 20, 20, 20);
	Planet::collider = new SphereCollider(&this->position, 20, 22.5, 22.5, 22.5);
	Planet::texture = new Texture("./Resources/planetTexture.bmp", this->size);
}

Planet::~Planet()
{
}

void Planet::drawScene()
{
	glPushMatrix();
	glTranslatef(this->position.x, this->position.y, this->position.z);
	/*glRotatef(discAngle, 0, 0, 0);*/
	glRotatef(discAngle, 1, 0, 1);
	texture->drawScene();
	glCallList(this->base);
	glPopMatrix();

	if (debugMode) {
		this->collider->Draw();
	}
}

unsigned int Planet::setupDrawing(unsigned int baseList)
{
	texture->setup();

	float matAmb[] = { this->color.red / 255, this->color.green / 255, this->color.blue / 255, 1.0 };

	this->base = ++baseList;
	glNewList(this->base, GL_COMPILE);
	glPushMatrix();
	glColor4f(this->color.red, this->color.green, this->color.blue, this->color.alpha);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matAmb);
	glutSolidSphere(this->size, 20, 20);
	glColor4f(this->color.red / 2, this->color.green / 2, this->color.blue / 2, this->color.alpha / 2);
	glRotatef(discAngle, 1, 0, 0);
	glutSolidTorus(1, discSize, 40, 40);
	//glRotatef(discAngle/2, 1, 0, 0);
	//glutSolidTorus(1, 25, 40, 40);
	//glRotatef(discAngle/2, 1, 0, 0);
	//glutSolidTorus(1, 25, 40, 40);
	glPopMatrix();
	glEndList();
	/*std::cout << this->texture->imageAddress << std::endl;*/
	return this->base;
}

void Planet::start()
{
}

void Planet::update(int deltaTime)
{
	/*this->heading = glm::rotate();*/
	/*this->position.z -= 20 * (deltaTime / 1000.0);*/
	discAngle += 0.25f;
	if (discAngle == 360.0f) {
		discAngle = 0.0f;
	}

	//std::cout << discAngle << std::endl;

	float moveStepX = speedX * (deltaTime / 1000.0);
	float moveStepY = speedY * (deltaTime / 1000.0);
	float moveStepZ = speedZ * (deltaTime / 1000.0);

	this->heading.x = moveStepX;
	this->heading.z = moveStepZ;
	this->heading.y = moveStepY;

	this->position += this->heading;

	if (this->momentum > 0) {
		this->momentum -= 0.15f;
	}
	if (this->momentum < 0) {
		this->momentum += 0.15f;
	}

	if (speedX > 0) {
		speedX -= 0.1f;
	}

	if (speedX < 0) {
		speedX += 0.1f;
	}

	if (speedY > 0) {
		speedY -= 0.1f;
	}

	if (speedY < 0) {
		speedY += 0.1f;
	}


	if (speedZ > 0) {
		speedZ -= 0.1f;
	}

	if (speedZ < 0) {
		speedZ += 0.1f;
	}
}

void Planet::collides(GameObject * other)
{
	if (debugMode) {
		std::cout << "Planet collides!" << std::endl;
	}

	this->momentum += other->momentum /mass;

	glm::vec3 direction = glm::normalize(*this->collider->colliderCentre - *other->collider->colliderCentre) * this->momentum;

	speedX = direction.x;
	speedY = direction.y;
	speedZ = direction.z;
}
