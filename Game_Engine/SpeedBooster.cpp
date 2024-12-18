#include "SpeedBooster.h"



SpeedBooster::SpeedBooster(glm::vec3 pos, Color col) : GameObject(position)
{
	this->position = pos;

	this->color = col;

	SpeedBooster::collider = new CubeCollider(&this->position, 2, 2, 2);
}


SpeedBooster::~SpeedBooster()
{
	delete SpeedBooster::collider;

	SpeedBooster::collider = NULL;
}

void SpeedBooster::drawScene()
{
	glPushMatrix();
	glTranslatef(this->position.x, this->position.y, this->position.z);
	glCallList(this->base);


	glPopMatrix();

	if (debugMode) {

		this->collider->Draw();

	}
}

void SpeedBooster::start()
{

}

void SpeedBooster::update(int deltaTime)
{

}

unsigned int SpeedBooster::setupDrawing(unsigned int baseList)
{
	float lightAmb[] = { 0.2, 0.2, 0.2, 1.0 };
	float lightDifAndSpec[] = { 0.3, 0.3, 0.3, 1.0 };

	//glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec);

	float matAmb[] = { this->color.red / 255, this->color.green / 255, this->color.blue / 255, 1.0 };

	float matDif[] = { this->color.red / 255, this->color.green / 255, this->color.blue / 255, 1.0 };

	this->heading = glm::vec3(0.0, 0.0, 0.0);

	this->base = ++baseList;

	glNewList(this->base, GL_COMPILE);

	glPushMatrix();

	glColor4f(this->color.red, this->color.green, this->color.blue, this->color.alpha);

	glMaterialfv(GL_FRONT, GL_AMBIENT, matAmb);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, matDif);

	//glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmb);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDifAndSpec);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, lightDifAndSpec);

	glutSolidSphere(1.0, 40, 40);

	glPopMatrix();

	glEndList();

	return this->base;
}

void SpeedBooster::collides(GameObject * other)
{
	other->momentum *= 4;
}
