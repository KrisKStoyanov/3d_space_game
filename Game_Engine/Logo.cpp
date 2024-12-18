#include "Logo.h"



Logo::Logo()
{
}


Logo::~Logo()
{
}

void Logo::drawScene(void)
{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
	glLoadIdentity();
	glColor4f(1, 1, 1, 1);
	glTranslatef(0.0, 0.0, -1.0);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_POLYGON);
	glTexCoord2f(0, 0); glVertex3f(-1.0, -1.0, -2);
	glTexCoord2f(1, 0); glVertex3f(1.0, -1.0, -2);
	glTexCoord2f(1, 1); glVertex3f(1.0, 1.0, -2);
	glTexCoord2f(0, 1); glVertex3f(-1.0, 1.0, -2);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glLoadIdentity();
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 1.0, 1.0);
	/*glRasterPos3f(-1.0, 1.0, -2.0);*/
	glRasterPos3f(0.57f, .5f , -1.5);
	gameInstructions.writeBitmapString((void*)gameInstructions.font, "Instructions:");
	glRasterPos3f(0.57f, 0.4f, -1.5);
	gameInstructions.writeBitmapString((void*)gameInstructions.font, "Arrow Keys to move and turn");
	glRasterPos3f(0.57f, 0.3f, -1.5);
	gameInstructions.writeBitmapString((void*)gameInstructions.font, "Page Up and Page Down to");
	glRasterPos3f(0.57f, 0.2f, -1.5);
	gameInstructions.writeBitmapString((void*)gameInstructions.font, "steer the space ship vertically");
	glRasterPos3f(0.57f, 0.1f, -1.5);
	gameInstructions.writeBitmapString((void*)gameInstructions.font, "[1],[2],[3],[4],[5]");
	glRasterPos3f(0.57f, 0.0f, -1.5);
	gameInstructions.writeBitmapString((void*)gameInstructions.font, "to change between cameras");
	glRasterPos3f(0.57f, -0.1f, -1.5);
	gameInstructions.writeBitmapString((void*)gameInstructions.font, "[R] to reset the level");
	glRasterPos3f(0.57f, -0.2f, -1.5);
	gameInstructions.writeBitmapString((void*)gameInstructions.font, "Hitting asteroids will reduce");
	glRasterPos3f(0.57f, -0.3f, -1.5);
	gameInstructions.writeBitmapString((void*)gameInstructions.font, "the ship's durability. ");
	glRasterPos3f(0.57f, -0.4f, -1.5);
	gameInstructions.writeBitmapString((void*)gameInstructions.font, "Dropping below 0 will");
	glRasterPos3f(0.57f, -0.5f, -1.5);
	gameInstructions.writeBitmapString((void*)gameInstructions.font, "restart the game.");
	glPopMatrix();

	glDisable(GL_TEXTURE_2D); // Restore texturing.   
	glEnable(GL_LIGHTING); // Restore lighting.
	glEnable(GL_BLEND);
}

void Logo::setup(void)
{
	//glClearColor(0.0, 0.0, 0.0, 0.0);
	//glEnable(GL_DEPTH_TEST); // Enable depth testing.

	//float globAmb[] = { 1, 1, 1, 1.0 };

	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

	//float matAmbAndDif[] = { 1.0, 1.0, 1.0, 1.0 };
	//float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	//float matShine[] = { 10.0 };

	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

	for (int i = 0; i < 4 * image->sizeY * image->sizeX; i += 4) {
		if (
			image->data[i] < 10 &&
			image->data[i + 1] < 150 &&
			image->data[i + 2] < 150
			) {
			image->data[i + 3] = 0x00;
		}
	}

	// Create texture ids.
	glGenTextures(1, texture);

	// Load external textures.
	loadExternalTextures();

	// Specify how texture values combine with current surface color values.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Turn on OpenGL texturing.
	glEnable(GL_TEXTURE_2D);
}

void Logo::loadExternalTextures()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->sizeX, image->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
