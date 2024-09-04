#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Color.h"




#include <iostream>
#include <cassert>



using namespace std;

GraphicsBuffer* GraphicsSystem::mpBackBuffer=nullptr;


GraphicsSystem::GraphicsSystem()
{
	//init any member variables to default values
	mpDisplay = nullptr;

	mWidth = 0;
	mHeight = 0;
	//DO NOT call init
}

GraphicsSystem::~GraphicsSystem()
{
	//make sure you call cleanup
	cleanup();
}

bool GraphicsSystem::init(unsigned int width, unsigned int height)
{
	//init all allegro subsystems (and allegro itself)
	// create a display of size width X height
	// create the backbuffer GraphicsBuffer
	mWidth = width;
	mHeight = height;

	

	//creates a display

	//are we suposed to be allowed to have mulitple windows open?

	if (mpDisplay != nullptr)
	{
		cleanup();
	}

	mpDisplay = new sf::RenderWindow(sf::VideoMode(width,height), "Game");

	mpBackBuffer = new GraphicsBuffer(mpDisplay);

	
	//return true if everything is initted properly
	return true;
}

void GraphicsSystem::cleanup()
{
	delete mpDisplay;

	delete mpBackBuffer;

}

void GraphicsSystem::flip()
{

	sf::Image tempImage(*GraphicsSystem::getBackBuffer()->getImage());
	sf::Texture tempTex;
	std::vector<sf::Sprite> sprites = GraphicsSystem::getBackBuffer()->getSpriteObjects();
	tempTex.loadFromImage(tempImage);
	tempTex.setRepeated(false);

	mpDisplay->clear();
	

	for (unsigned int i = 0; i < GraphicsSystem::getBackBuffer()->getSpriteObjects().size(); i++)
	{
		sf::Sprite spritesToDraw = GraphicsSystem::getBackBuffer()->getSpriteObjects().at(i);
		mpDisplay->draw(spritesToDraw);
	}

	for (unsigned int i = 0; i < GraphicsSystem::getBackBuffer()->getTextObjects().size(); i++)
	{
		sf::Text textToDraw = GraphicsSystem::getBackBuffer()->getTextObjects().at(i);
		mpDisplay->draw(textToDraw);

	}

//	mpDisplay->draw(sf::Sprite(tempTex));

	mpDisplay->display();
}

