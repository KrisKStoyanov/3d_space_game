#pragma once
#include "Skybox.h"

Skybox::Skybox()
{
}

Skybox::~Skybox()
{
}



// Initialization routine.
void Skybox::setup(void)
{
//	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glEnable(GL_DEPTH_TEST); // Enable depth testing.

	//float globAmb[] = { 1, 1, 1, 1.0 };

	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
													  
	float matAmbAndDif[] = { 1.0, 1.0, 1.0, 1.0 };
	float matSpec[] = { 1.0, 1.0, 1.0, 1.0 };
	float matShine[] = { 2.5 };

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);


	// Create texture ids.
	glGenTextures(6, texture);

	// Load external textures.
	loadExternalTextures();

	// Specify how texture values combine with current surface color values.
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Turn on OpenGL texturing.
	glEnable(GL_TEXTURE_2D);

						// Cull back faces.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
}

void Skybox::loadExternalTextures()
{
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageBottom->sizeX, imageBottom->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBottom->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageFront->sizeX, imageFront->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageFront->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageTop->sizeX, imageTop->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageTop->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageLeft->sizeX, imageLeft->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageLeft->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageRight->sizeX, imageRight->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageRight->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageBack->sizeX, imageBack->sizeY, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageBack->data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

// Drawing routine.
void Skybox::drawScene(glm::vec3 playerlocation, float windowSize)
{
	/*glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);*/
	
	//glLoadIdentity();

	glPushMatrix();
	//glTranslatef(playerlocation.x, playerlocation.y, playerlocation.z);
	//glPushAttrib(GL_ENABLE_BIT);
	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);

	glColor4f(1, 1, 1, 1);

	//down
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
		/*glNormal3f(0.0, 1.0, 0.0);*/
	glTexCoord2f(1, 1); glVertex3f(playerlocation.x + windowSize, playerlocation.y - windowSize, playerlocation.z - windowSize);
	glTexCoord2f(0, 1); glVertex3f(playerlocation.x - windowSize, playerlocation.y - windowSize, playerlocation.z - windowSize);
	glTexCoord2f(0, 0); glVertex3f(playerlocation.x - windowSize, playerlocation.y - windowSize, playerlocation .z+ windowSize);
	glTexCoord2f(1, 0); glVertex3f(playerlocation.x + windowSize, playerlocation.y - windowSize, playerlocation .z+ windowSize);
	glEnd();

	//front
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);
		/*glNormal3f(0.0, 0.0, 1.0);*/
		glTexCoord2f(0, 0); glVertex3f(playerlocation.x - windowSize, playerlocation.y - windowSize, playerlocation.z - windowSize);
		glTexCoord2f(1, 0); glVertex3f(playerlocation.x + windowSize, playerlocation.y - windowSize, playerlocation.z - windowSize);
		glTexCoord2f(1, 1); glVertex3f(playerlocation .x+ windowSize, playerlocation .y+ windowSize, playerlocation.z - windowSize);
		glTexCoord2f(0, 1); glVertex3f(playerlocation.x - windowSize, playerlocation .y+ windowSize, playerlocation.z - windowSize);
	glEnd();

	//top
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);
		/*glNormal3f(0.0, 1.0, 0.0);*/
	glTexCoord2f(1, 0); glVertex3f(playerlocation .x+ windowSize, playerlocation .y+ windowSize, playerlocation.z - windowSize);
	glTexCoord2f(1, 1); glVertex3f(playerlocation .x+ windowSize, playerlocation .y+ windowSize, playerlocation .z+ windowSize);
	glTexCoord2f(0, 1); glVertex3f(playerlocation .x- windowSize, playerlocation .y+ windowSize, playerlocation .z+ windowSize);
	glTexCoord2f(0, 0); glVertex3f(playerlocation .x- windowSize, playerlocation .y+ windowSize, playerlocation .z- windowSize);
	glEnd();

	//left
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);
		/*glNormal3f(-1.0, 0.0, 0.0);*/
		glTexCoord2f(1, 0); glVertex3f(playerlocation.x - windowSize, playerlocation.y - windowSize, playerlocation.z - windowSize);
		glTexCoord2f(1, 1); glVertex3f(playerlocation.x - windowSize, playerlocation .y+ windowSize, playerlocation.z - windowSize);
		glTexCoord2f(0, 1); glVertex3f(playerlocation.x - windowSize, playerlocation .y+ windowSize, playerlocation.z + windowSize);
		glTexCoord2f(0, 0); glVertex3f(playerlocation.x - windowSize, playerlocation .y- windowSize, playerlocation.z + windowSize);
	glEnd();

	//right
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
		/*glNormal3f(1.0, 0.0, 0.0);*/
		glTexCoord2f(0, 0); glVertex3f(playerlocation .x+ windowSize, playerlocation.y - windowSize, playerlocation.z - windowSize);
		glTexCoord2f(1, 0); glVertex3f(playerlocation .x+ windowSize, playerlocation.y - windowSize, playerlocation .z+ windowSize);
		glTexCoord2f(1, 1); glVertex3f(playerlocation .x+ windowSize, playerlocation .y+ windowSize, playerlocation .z+ windowSize);
		glTexCoord2f(0, 1); glVertex3f(playerlocation .x+ windowSize, playerlocation .y+ windowSize, playerlocation.z - windowSize);
	glEnd();

	//behind
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);
	/*glNormal3f(0.0, 0.0, 1.0);*/
		glTexCoord2f(0, 0); glVertex3f(playerlocation .x+ windowSize, playerlocation.y - windowSize, playerlocation .z+ windowSize);
		glTexCoord2f(1, 0); glVertex3f(playerlocation.x - windowSize, playerlocation.y - windowSize, playerlocation .z+ windowSize);
		glTexCoord2f(1, 1); glVertex3f(playerlocation.x - windowSize, playerlocation .y+ windowSize, playerlocation .z+ windowSize);
		glTexCoord2f(0, 1); glVertex3f(playerlocation .x+ windowSize, playerlocation .y+ windowSize, playerlocation .z+ windowSize);
	glEnd();

	//glPopAttrib();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D); // Restore texturing.   
	glEnable(GL_LIGHTING); // Restore lighting.
	glEnable(GL_BLEND);
	//glEnable(GL_DEPTH_TEST);
	//glutPostRedisplay();
	/*glutSwapBuffers();*/
}


