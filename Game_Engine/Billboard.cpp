#include "Billboard.h"
//#include "GameEngine.h"


Billboard::Billboard(glm::vec3 pos, GameObject * player,float resX, float resY, std::string imageAddress) : GameObject(position)
{
	this->position = pos;
	this->player = player;
	this->resX = resX;
	this->resY = resY;
	this->imageAddress = imageAddress;
	image = getbmp(imageAddress);
}


Billboard::~Billboard()
{
}


void Billboard::setup(void)
{

}

void Billboard::drawScene(void)
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glTranslatef(this->position.x, this->position.y, this->position.z);
	glm::vec3 locationDistance = this->position - player->position;

	/*std::cout << "x: " <<  locationDistance.x << "y: " <<  locationDistance.y << "z: " << locationDistance.z << std::endl;*/

	float normal = atan(locationDistance.x / locationDistance.z) * (180 / PI);
	if (locationDistance.z > 0) {
		normal += 180;
	}
	glRotatef(normal, 0, 1, 0);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glColor3f(1, 1, 1);
	glNormal3f(0, 0, -1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-10, -10, 0);
	glTexCoord2f(1, 0); glVertex3f(30, -10, 0);
	glTexCoord2f(1.55, 1); glVertex3f(30, 10, 0);
	glTexCoord2f(0.58, 1); glVertex3f(-10, 10, 0);
	glEnd();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
}

void Billboard::loadTexture()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, texture);
	BitMapFile* image;
	image = getbmp(imageAddress);

	for (int i = 0; i < 4 * image->sizeY * image->sizeX; i += 4) {
		if (
			image->data[i] > 117 &&
			image->data[i + 1] > 117 &&
			image->data[i + 2] > 117
			) {
			image->data[i + 3] = 0x00;
		}
	}

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->sizeX, image->sizeY, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}

void Billboard::start(void)
{
	loadTexture();
}

void Billboard::update(int deltaTime)
{
}
