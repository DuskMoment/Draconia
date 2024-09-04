#pragma once

#include <Trackable.h>
#include <Vector2D.h>

#include <allegro5/allegro.h>



#include "Color.h"
#include "Font.h"

#include <SFML/Graphics.hpp>

//new includes


class GraphicsBuffer;
class Sprite;

class GraphicsSystem :public Trackable
{
public:
	GraphicsSystem();//should not call init
	~GraphicsSystem();//should call cleanup

	//make sure initting multiple times in a row doesn't fail
	bool init(unsigned int width, unsigned int height);//make sure initting multiple times in a row doesn't fail
	
	//make sure calling cleanup never fails
	void cleanup();

	unsigned int getDisplayWidth() const { return mWidth; };
	unsigned int getDisplayHeight() const { return mHeight; };

	sf::RenderWindow* getWindow() { return mpDisplay; };
	
	static GraphicsBuffer* getBackBuffer() { return mpBackBuffer; };

	void flip();//flip the allegro display

private:
	sf::RenderWindow* mpDisplay = nullptr;
	static GraphicsBuffer* mpBackBuffer;

	unsigned int mWidth = 0;
	unsigned int mHeight = 0;

	bool initAddOns();
	sf::RenderWindow* getDisplay() const { return mpDisplay; };


};
