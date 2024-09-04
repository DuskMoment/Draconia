#include <iostream>
#include <cassert>
#include <string>
#include <random>
#include <ctime>

#include <PerformanceTracker.h>
#include <MemoryTracker.h>

#include <GraphicsSystem.h>
#include <GraphicsBuffer.h>
#include <Sprite.h>
#include <Color.h>
#include <Font.h>

#include <EventSystem.h>
#include "Game.h"

#include <SFML/Graphics.hpp>


using namespace std;

//gloabal for game 

int main()
{
	//sf::RenderWindow window(sf::VideoMode(800, 600), "this sucks");



	//sf::Image image;

	//image.create(640, 480, sf::Color::Blue);

	//
	////sf::Sprite sprite(tex);

	//std::vector<sf::Sprite> spriteVec;

	//{
	//	sf::Texture tex;
	//	tex.loadFromImage(image);

	//	sf::Sprite tempSprite;

	//	tempSprite.setTexture(tex);
	//	spriteVec.push_back(tempSprite);

	//}

	//window.draw(spriteVec.at(0));

	//window.display();
	//system("pause");

	//return 0;


//	//sf::RenderTexture renderTex;
//
//	////create and draw to the renderWindow
//	//renderTex.create(800, 600);
//	//renderTex.clear();
//	//renderTex.draw(sprite);
//
//	////clear the regular window
//	//window.clear();
//	//
//	//window.draw(sf::Sprite(renderTex.getTexture()));
//	//window.display();
//	//
//	//Timer timer;
//	//timer.sleep(5.0 * 1000);
//
//
//	//sf::Sprite blueSprite;
//	//sf::Sprite redSprite;
//
//	//sf::RenderTexture redBuffer;
//	//sf::RenderTexture blueBuffer;
//
//	//sf::Image redImage;
//	//sf::Image blueImage;
//
//	//redImage.create(400, 400, sf::Color::Red);
//	//blueImage.create(200, 200, sf::Color::Blue);
//
//	//redImage.copy(blueImage, 20, 40, sf::IntRect(0,0, blueImage.getSize().x*1, blueImage.getSize().y*1), false);
//
//	//sf::Texture redTex;
//	//
//	//redTex.loadFromImage(redImage);
//
//	//redBuffer.create(800, 600);
//	//redBuffer.clear();
//	//redBuffer.draw(sf::Sprite(redTex));
//
//	//window.clear();
//	//window.draw(sf::Sprite(redTex));
//	//window.display();
	/*const string ASSET_PATH = "..\\..\\shared\\assets\\";
	const string SMURF_FILENAME = "smurf_sprites.png";

	GraphicsSystem theSystem;
	theSystem.init(800, 600);
	GraphicsBuffer theBuffer(400,200, Color(1.0f,1.0f,1.0f));
	GraphicsBuffer secondBuffer(300, 200, Color(0.5f, 1.f, 0.2f));
	GraphicsBuffer* pSmurfBuffer = new GraphicsBuffer(ASSET_PATH + SMURF_FILENAME);
	const string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 20;
	Font* pFont = new Font(ASSET_PATH + FONT_FILENAME, FONT_SIZE);

	const Color BLACK(0, 0, 0);
	const Color WHITE(1.0f, 1.0f, 1.0f);


	const unsigned int PIXEL_WIDTH = 60;
	const unsigned int PIXEL_HEIGHT = 60;
	const unsigned int SPRITES_ACROSS = 4;
	const unsigned int SPRITES_DOWN = 4;
	Sprite sprites[SPRITES_ACROSS * SPRITES_DOWN];
	unsigned int spriteNum = 0;

	for (unsigned int x = 0; x < SPRITES_ACROSS; x++)
	{
		for (unsigned int y = 0; y < SPRITES_DOWN; y++)
		{
			Sprite sprite(pSmurfBuffer, Vector2D((int)(x * PIXEL_WIDTH), (int)(y * PIXEL_HEIGHT)), PIXEL_WIDTH, PIXEL_HEIGHT);
			sprites[spriteNum] = sprite;
			spriteNum++;
		}
	}

	secondBuffer.writeText(Vector2D(400, 0), *pFont, WHITE, "Curse you Papa Smurf!!!", Font::LEFT);
	GraphicsSystem::getBackBuffer()->draw(Vector2D(0, 0), secondBuffer, 1.0);

	GraphicsSystem::getBackBuffer()->draw(Vector2D(400, 300), theBuffer, 1.0);
	GraphicsSystem::getBackBuffer()->draw(Vector2D(400, 300), sprites[3], 1.0);
	

	theSystem.flip();

	Timer timer;
	timer.sleep(5.0 * 1000);*/
	

	
	EventSystem::createInstance();
	EventSystem::getInstance()->init();

	Game::createInstance();
	Game* pGame = Game::getInstance();
	pGame->init(800,600);

	pGame->doLoop();

	Game::deleteInstance();
	pGame = nullptr;

	EventSystem::destroyInstance();

	MemoryTracker::getInstance()->reportAllocations(cout);
	system("pause");

    return 0;
	
}