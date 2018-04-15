#include "Star.h"
#include <WinBase.h>



Star::Star(glm::vec3 pos, Color col, float size) : GameObject (position)
{
	this->position = pos;

	this->color = col;

	this->size = size;

	this->orbitVector = this->position;
}


Star::~Star()
{
	delete Star::collider;
}

void Star::drawScene()
{
	float lightAmb[] = { 0.2, 0.2, 0.2, 1.0 };
	float lightDifAndSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float lightPos[] = { 1.0, 2.0, 0.0, 1.0 };

	glPushMatrix();
	glTranslatef(this->position.x, this->position.y, this->position.z);
	glCallList(this->base);

	//glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);

	//glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);

	glPopMatrix();

	glPushMatrix();
	lightPos[0] = this->position.x, lightPos[1] = this->position.y, lightPos[2] = this->position.z;
	//glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.5);
	//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.005);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.00001);

	glPopMatrix();

	//if (debugMode) {

	//	this->collider->Draw();
	//}
}

void Star::start()
{

}

void Star::update(int deltaTime)
{
	waitTime += 0.05;
	if(waitTime >= 0.2){
		this->position.x += (1000 * cos(t)) * (deltaTime / 1000.0)/4;
		this->position.y += (1000 * sin(t)) * (deltaTime / 1000.0)/4;
		this->position.z += (1000 * sin(t)) * (deltaTime / 1000.0)/4;
		t += (2 * PI / 100)/4;
		waitTime = 0;
	}

}

unsigned int Star::setupDrawing(unsigned int baseList)
{
	float matAmb[] = { 1, 1, 1, 1.0 };

	float matDif[] = { 1, 1, 1, 1.0 };

	float matSpec[] = {1 ,1 , 1, 1 };

	float matEmis[] = { 0.1 , 0.1, 0.1 , 1.0};

	float matShine[] = { 128 };

	this->base = ++baseList;

	glNewList(this->base, GL_COMPILE);

	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

	glMaterialfv(GL_FRONT, GL_EMISSION, matEmis);
	glDisable(GL_LIGHTING);

	glColor4f(this->color.red, this->color.green, this->color.blue, this->color.alpha);

	glutSolidSphere(this->size, 20, 20);

	glEnable(GL_LIGHTING);

	glPopMatrix();

	glEndList();

	return this->base;
}

void Star::collides(GameObject * other)
{
	if (debugMode) {
		std::cout << "Star collides, star will be removed!" << std::endl;
	}

	this->momentum += other->momentum / mass;

	glm::vec3 direction = glm::normalize(*this->collider->colliderCentre - *other->collider->colliderCentre) * this->momentum;

	speedX = direction.x;
	speedY = direction.y;
	speedZ = direction.z;
}

