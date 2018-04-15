#include "Asteroid.h"


Asteroid::Asteroid(glm::vec3 pos, Color col, float size) : GameObject(position)

{

	this->position = pos;

	this->color = col;

	this->size = size;

	//Asteroid::collider = new CubeCollider(&this->position, 2, 2, 2);

	Asteroid::collider = new SphereCollider(&this->position, 20, 1.5, 1.5, 1.5);

	Asteroid::texture = new Texture("./Resources/astTexture.bmp", this->size);

}



Asteroid::~Asteroid()

{

	delete Asteroid::collider;

	Asteroid::collider = NULL;

}


void Asteroid::drawScene()

{

	glPushMatrix();
	glTranslatef(this->position.x, this->position.y, this->position.z);
	texture->drawScene();
	glCallList(this->base);

	glPopMatrix();

	if (debugMode) {

		this->collider->Draw();

	}

}


void Asteroid::start()

{


}


void Asteroid::update(int deltaTime)

{
	float moveStepX = speedX * (deltaTime / 1000.0);
	float moveStepY = speedY * (deltaTime / 1000.0);
	float moveStepZ = speedZ * (deltaTime / 1000.0);

	this->heading.x = moveStepX;
	this->heading.z = moveStepZ;
	this->heading.y = moveStepY;

	this->position += this->heading;

	if (this->momentum > 0) {
		this->momentum -= 0.05f;
	}
	if (this->momentum < 0) {
		this->momentum += 0.05f;
	}

	if (speedX > 0) {
		speedX -= 0.05f;
	}

	if (speedX < 0) {
		speedX += 0.05f;
	}

	if (speedY > 0) {
		speedY -= 0.05f;
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


unsigned int Asteroid::setupDrawing(unsigned int baseList)

{
	texture->setup();

	float matAmb[] = { this->color.red / 255, this->color.green / 255, this->color.blue / 255, 1.0 };

	this->heading = glm::vec3(0.0, 0.0, 0.0);

	this->base = ++baseList;

	glNewList(this->base, GL_COMPILE);

	glPushMatrix();

	glColor4f(this->color.red, this->color.green, this->color.blue, this->color.alpha);
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matAmb);

	glutSolidSphere(this->size, 20, 20);

	glPopMatrix();

	glEndList();

	return this->base;
}


void Asteroid::collides(GameObject* other) {

	if (debugMode) {
		std::cout << "Asteroid collides, asteroid will be removed!" << std::endl;
	}

	this->momentum += other->momentum / this->mass;

	glm::vec3 direction = glm::normalize(*this->collider->colliderCentre - *other->collider->colliderCentre) * this->momentum;

	speedX = direction.x;
	speedY = direction.y;
	speedZ = direction.z;

	//this->heading = glm::normalize(*other->collider->colliderCentre - *this->collider->colliderCentre);

	/*if (other->collider->colliderCentre->x > this->collider->colliderCentre->x) {
		speedX += -glm::abs(this->collider->colliderCentre->x - other->collider->colliderCentre->x) * (other->momentum / 2);
		std::cout << "x: " << other->collider->colliderCentre->x << " - " << this->collider->colliderCentre->y << std::endl;
	}
	if (other->collider->colliderCentre->y > this->collider->colliderCentre->y) {
		speedY += -glm::abs(this->collider->colliderCentre->y - other->collider->colliderCentre->y) * (other->momentum / 2);
		std::cout << "y: " << other->collider->colliderCentre->y << " - " << this->collider->colliderCentre->y << std::endl;
	}
	if (other->collider->colliderCentre->z > this->collider->colliderCentre->z) {
		speedZ += -glm::abs(this->collider->colliderCentre->z - other->collider->colliderCentre->z) * (other->momentum / 2);
		std::cout << "z: " << other->collider->colliderCentre->z << " - " << this->collider->colliderCentre->z << std::endl;
	}
	if (other->collider->colliderCentre->x < this->collider->colliderCentre->x) {
		speedX += glm::abs(this->collider->colliderCentre->x - other->collider->colliderCentre->x) * (other->momentum / 2);
		std::cout << "x: " << other->collider->colliderCentre->x << " - " << this->collider->colliderCentre->x << std::endl;
	}
	if (other->collider->colliderCentre->y < this->collider->colliderCentre->y) {
		speedY += glm::abs(this->collider->colliderCentre->y - other->collider->colliderCentre->y) * (other->momentum / 2);
		std::cout << "y: " << other->collider->colliderCentre->y << " - " << this->collider->colliderCentre->y << std::endl;
	}
	if (other->collider->colliderCentre->z < this->collider->colliderCentre->z) {
		speedZ += glm::abs(this->collider->colliderCentre->z - other->collider->colliderCentre->z) * (other->momentum / 2);
		std::cout << "z: " << other->collider->colliderCentre->z << " - " << this->collider->colliderCentre->z << std::endl;
	}*/
	/*this->active = false;*/

}

