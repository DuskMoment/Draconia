#include "Color.h"

Color::Color(int r, int g, int b, int a /*= 255*/)
{
	//implement this
	mR = r;
	mG = g;
	mB = b;
	mA = a;
}

Color::Color(float r, float g, float b, float a /*= 1.0f*/)
{
	//implement this
	mR = r * 255;
	mG = g * 255;
	mB = b * 255;
	mA = a * 255;
}

sf::Color Color::getSFColorFromColor(const Color& color)
{
	//call al_map_rgba or al_map_rgba_f
	//does this need to be destroyed?
	sf::Color sfColor(color.getR(), color.getG(), color.getB(), color.getA());
	return sfColor;
}


