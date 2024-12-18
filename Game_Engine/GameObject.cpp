#include "GameObject.h"

std::map <int, bool> GameObject::specialKeys;
std::map <char, bool> GameObject::keys;

bool GameObject::debugMode;

GameObject::GameObject(glm::vec3 pos)
{
	this->position = pos;
}


GameObject::~GameObject()
{

}

unsigned int GameObject::setupDrawing(unsigned int listBase)
{
	return 0;
}

void GameObject::drawScene()
{
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// Position the objects for viewing.
	gluLookAt(0.0, 0.0, -10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);*/
}

void GameObject::collides(GameObject * other)
{

}

