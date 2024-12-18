#include <cmath>
#include <cstdlib>

#include "GameObject.h"
#include "BitMapFile.h"

class Skybox
{
public:
	Skybox();
	~Skybox();
	void drawScene(glm::vec3 playerLocation, float windowSize);
	void setup(void);
	void loadExternalTextures();

	unsigned int texture[6];
	BitMapFile *imageTop = getbmp("../Resources/Skybox/top.bmp");
	BitMapFile *imageFront = getbmp("../Resources/Skybox/front.bmp");
	BitMapFile *imageBack = getbmp("../Resources/Skybox/back.bmp");
	BitMapFile *imageLeft = getbmp("../Resources/Skybox/left.bmp");
	BitMapFile *imageRight = getbmp("../Resources/Skybox/right.bmp");
	//Back
	BitMapFile *imageBottom = getbmp("../Resources/Skybox/bottom.bmp");
};

