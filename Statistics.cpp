#include "Statistics.h"


Statistics::Statistics()
{
}


Statistics::~Statistics()
{
}

void Statistics::writeBitmapString(void * font, char * string)
{
	char *c;

	for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

void Statistics::floatToString(char * destStr, int precision, float val)
{
	//destStr = std::to_string(val);
	snprintf(destStr, sizeof(destStr), "%f", val);
	destStr[precision] = '\0';
}
