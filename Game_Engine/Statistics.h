#pragma once
/* OPENGL_INCLUDES */
#ifndef OPENGL_INCLUDES
#define OPENGL_INCLUDES
#  include <GL/glew.h>
#  include <GL/freeglut.h>
#  include <GL/glext.h>
#pragma comment(lib, "glew32.lib") 
#endif 

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

class Statistics
{
public:
	Statistics();
	~Statistics();
	char theStringBuffer[10];
	long font = (long)GLUT_BITMAP_8_BY_13;
	void writeBitmapString(void *font, char *string);
	void floatToString(char * destStr, int precision, float val);

};

