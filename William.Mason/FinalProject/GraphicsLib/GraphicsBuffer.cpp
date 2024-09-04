#include "GraphicsBuffer.h"
#include "GraphicsSystem.h"
#include "Color.h"
#include "Sprite.h"
#include "Font.h"

GraphicsBuffer::GraphicsBuffer(sf::RenderWindow* pDisplay)
{
	//get backbuffer and set mpBitmap to that
	//mpBitmap = al_get_backbuffer(pDisplay);
	
	float xSize = pDisplay->getSize().x;
	float ySize = pDisplay->getSize().y;
	mpImage = new sf::Image();
	mpTexture = new sf::Texture();


	assert(mpImage);

	mpImage->create(xSize, ySize);
	mpTexture->loadFromImage(*mpImage);
	
}

GraphicsBuffer::GraphicsBuffer(const std::string& filename)
{
	//load bitmap from the given file
	//remove

	mpImage = new sf::Image();
	mpTexture = new sf::Texture();

	mpImage->loadFromFile(filename);

	assert(mpImage->loadFromFile(filename));
	//mpTexture->loadFromFile(filename);

	//assert(mpBitmap);
	sf::Sprite tempSprites;
	sf::Texture tempTex;

	mpTexture->loadFromImage(*mpImage);
	tempSprites.setTexture(*mpTexture);
	mSprites.push_back(tempSprites);

}

GraphicsBuffer::GraphicsBuffer(unsigned int width, unsigned int height, Color color)
{
	//create bitmap and set it to the given color
	//mpBitmap = al_create_bitmap(width,height);


	//make a new blank texture
	mpImage = new sf::Image();
	mpTexture = new sf::Texture();

	assert(mpImage);

	mpImage->create(width, height, Color::getSFColorFromColor(color));

	sf::Sprite tempSprite;
	sf::Texture texture;

	mpTexture->loadFromImage(*mpImage);
	tempSprite.setTexture(*mpTexture);

	mSprites.push_back(tempSprite);
	

}

GraphicsBuffer::~GraphicsBuffer()
{
	//make sure you destroy the bitmap (if appropriate)
	delete mpImage;
	delete mpTexture;

	mSprites.clear();
	mTextVec.clear();

}

GraphicsBuffer * GraphicsBuffer::clone() const
{
	//create new bitmap and copy all of "this" into it
	
	GraphicsBuffer* pNewBuffer = new GraphicsBuffer(this->getWidth(), this->getHeight());

	pNewBuffer->draw(Vector2D(0,0), *this);

	//GraphicsBuffer* pNewBuffer = nullptr;

	return pNewBuffer;
}

void GraphicsBuffer::draw(const Vector2D& destLoc, const GraphicsBuffer& src, double scale)
{
	sf::Image* pTarget = mpImage;//set the target bitmap

	assert(pTarget != src.mpImage);//make sure we are not trying to draw to and from the same bitmap
	if (pTarget != src.mpImage)
	{
		
		//get the texture from the scr.renderTexture
		
			std::vector<sf::Sprite> spriteCopy;
			for (unsigned int i = 0; i < src.mSprites.size(); i++)
			{
				
				spriteCopy.push_back(src.mSprites.at(i));
			}

			for (unsigned int i = 0; i < src.mSprites.size(); i++)
			{
				spriteCopy.at(i).setPosition(destLoc.getX(), destLoc.getY());

				spriteCopy.at(i).setScale(scale,scale);
			}

			for (unsigned int i = 0; i < src.mSprites.size(); i++)
			{
				this->mSprites.push_back(spriteCopy.at(i));
			}


			if (!src.mTextVec.empty())
			{
				for (unsigned int i = 0; i < src.mTextVec.size(); i++)
				{
					this->mTextVec.push_back(src.mTextVec.at(i));
				}
			}
		

	}
}


void GraphicsBuffer::draw(const Vector2D& destLoc, const Sprite& sprite, double scale /*= 1.0*/)
{
	sf::Image* pTarget = mpImage;
	GraphicsBuffer* pSrc = sprite.getBuffer();

	//do the same steps as in the other draw function - 
	//  make sure we are not drawing from and to the same bitmap

	assert(pTarget != pSrc->mpImage);
	if (pTarget != pSrc->mpImage)
	{
		
		//check the sources text vec and see if it needs to have text drawn to it
		
			std::vector<sf::Sprite> spriteCopy;
			for (unsigned int i = 0; i < pSrc->mSprites.size(); i++)
			{

				spriteCopy.push_back(pSrc->mSprites.at(i));
			}

			for (unsigned int i = 0; i < pSrc->mSprites.size(); i++)
			{
				spriteCopy.at(i).setPosition(destLoc.getX(), destLoc.getY());

				sf::IntRect rect(sprite.getSourceLoc().getX(), sprite.getSourceLoc().getY(),
					sprite.getWidth(), sprite.getHeight());
				spriteCopy.at(i).setTextureRect(rect);
				spriteCopy.at(i).setScale(scale, scale);
				
			}

			for (unsigned int i = 0; i < pSrc->mSprites.size(); i++)
			{
				this->mSprites.push_back(spriteCopy.at(i));
			}
	

		if (!pSrc->mTextVec.empty())
		{
			for (unsigned int i = 0; i < pSrc->mTextVec.size();i++)
			{
				this->mTextVec.push_back(pSrc->mTextVec.at(i));
			}
		}
		

	}

}

void GraphicsBuffer::writeText(const Vector2D& destLoc, const Font& font, const Color& color, const std::string& text)
{
	

	sf::Text myText;

	myText.setFont(*font.mpFont);
	myText.setString(text);
	myText.setCharacterSize(font.getSize());
	sf::Vector2f sfDestLoc(destLoc.getX(), destLoc.getY());
	myText.setPosition(sfDestLoc);
	myText.setFillColor(Color::getSFColorFromColor(color));

	mTextVec.push_back(myText);

}

void GraphicsBuffer::setToColor(const Color& color)
{
	
	mTextVec.clear();
	mSprites.clear();

	Vector2D size;
	size.setX(mpImage->getSize().x);
	size.setY(mpImage->getSize().y);

	delete mpImage;

	mpImage = new sf::Image();
	delete mpTexture;

	mpTexture = new sf::Texture();

	mpImage->create(size.getX(), size.getY(), Color::getSFColorFromColor(color));

	sf::Texture tempText;
	sf::Sprite tempSprite;

	
	mpTexture->loadFromImage(*mpImage);
	tempSprite.setTexture(*mpTexture);
	mSprites.push_back(tempSprite);

}

//void GraphicsBuffer::saveToFile(const std::string& filename) const
//{
//	//call al_save_bitmap
//
//	//al_save_bitmap(filename.c_str(), mpBitmap);
//}

