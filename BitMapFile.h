#pragma once
#include <string>
#include <fstream>
#include <iostream>

class BitMapFile
{
public:
	int sizeX;
	int sizeY;
	unsigned char *data;
};

BitMapFile *getbmp(std::string filename);

