#pragma once

#include <SFML/Graphics.hpp>


#include <Trackable.h>

#include <string>
#include "Color.h"
#include "Font.h"

class GraphicsSystem;
class Vector2D;
class Sprite;

class GraphicsBuffer : public Trackable
{
public:
	GraphicsBuffer(const std::string& filename);
	GraphicsBuffer(unsigned int width, unsigned int height, Color color = Color() );
	~GraphicsBuffer();

	GraphicsBuffer(sf::RenderWindow* pDisplay);//to be called by GraphicsSystem only

	GraphicsBuffer* clone() const;//return a new (dynamically allocated) buffer with the same contents as this

	unsigned int getWidth() const { return mpImage->getSize().x; };
	unsigned int getHeight() const { return  mpImage->getSize().y; };

	void draw(const Vector2D& destLoc, const GraphicsBuffer& src, double scale = 1.0);
	void draw(const Vector2D& destLoc, const Sprite& sprite, double scale = 1.0);
	void writeText(const Vector2D& destLoc, const Font& font, const Color& color, const std::string& text);
	void setToColor(const Color& color);
	//void saveToFile(const std::string& filename) const;

	//this is so we can draw to the screen
	sf::Image* getImage() { return mpImage; };
	std::vector<sf::Text> getTextObjects() { return mTextVec; };
	std::vector<sf::Sprite> getSpriteObjects() { return mSprites; };

private:
	
	sf::Image* mpImage = nullptr;
	std::vector<sf::Text> mTextVec;
	std::vector<sf::Sprite> mSprites;
	sf::Texture* mpTexture;


	//invalidate copy constructor and assignment operator - why?
	GraphicsBuffer(GraphicsBuffer&)=delete;
	GraphicsBuffer operator=(GraphicsBuffer&)=delete;
};
