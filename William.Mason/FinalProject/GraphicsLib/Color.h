#pragma once


#include <SFML/Graphics.hpp>
#include <Trackable.h>

class GraphicsSystem;

class Color :public Trackable
{
	friend class GraphicsBuffer;
public:
	Color() {};//default constructor
	Color(int r, int g, int b, int a = 255);//construct Color from int values
	Color(float r, float g, float b, float a = 1.0f);//construct Color from float values

	//implement these functions for real
	int getR() const { return mR; };
	int getG() const { return mG; };
	int getB() const { return mB; };
	int getA() const { return mA; };

private:
	//use variable(s) to hold values to represent color
	int mR = 0;
	int mG = 0;
	int mB = 0;
	int mA = 0;
	
	
	static sf::Color getSFColorFromColor(const Color& color);

};
