#pragma once

#include <Trackable.h>
#include <Vector2D.h>

class GraphicsBuffer;

class Sprite : public Trackable
{
public:
	Sprite(GraphicsBuffer* pBuffer, const Vector2D& ulCorner, unsigned int width, unsigned int height,
		int widthOffset = -1, int heightOffset = -1, int offsetX = 1, int offsetY = 1);
	Sprite();//default constructor
	~Sprite();//implement this destructor

	//implement these functions for real
	GraphicsBuffer* getBuffer() const { return mpBuffer; };
	const Vector2D& getSourceLoc() const { return mLoc; };
	unsigned int getWidth() const { return mWidth; };
	unsigned int getHeight() const { return mHeight; };

	Vector2D getWidthHeightHitBox() const { return Vector2D(mWidthHit, mHeightHit); };
	Vector2D getOffsetXY() const { return Vector2D(mLocOffsetX, mLocOffsetY); };

private:

	void generateHitBox(int widthOffset, int heightOffset, int offsetX, int offsetY);
	//add data
	GraphicsBuffer* mpBuffer = nullptr;

	Vector2D mLoc;

	int mWidth;
	int mHeight;

	//hit box mechanics 
	int mWidthHit;
	int mHeightHit;

	int mLocOffsetX;
	int mLocOffsetY;
};