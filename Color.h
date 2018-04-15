#pragma once
class Color
{
public:
	Color(float r = 1, float g = 1, float b = 1, float a = 1);
	~Color();
	float red;
	float green;
	float blue;
	float alpha;

	void modifyColor(float r, float g, float b, float a);
};

