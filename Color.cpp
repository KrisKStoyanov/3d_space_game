#include "Color.h"


Color::Color(float r, float g, float b, float a)
{
	this->red = r;
	this->green = g;
	this->blue = b;
	this->alpha = a;
}

Color::~Color()
{
}

void Color::modifyColor(float r, float g, float b, float a)
{
	this->red = r;
	this->green = g;
	this->blue = b;
	this->alpha = a;
}
