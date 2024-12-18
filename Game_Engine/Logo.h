#pragma once
#include "GameObject.h"
#include "BitMapFile.h"

class Logo
{
public:
	Logo();
	~Logo();
	void drawScene(void);
	void setup(void);
	void loadExternalTextures();
	unsigned int texture[1];
	BitMapFile *image = getbmp("../Resources/logo.bmp");
	bool active = true;
	Statistics gameInstructions;
};

