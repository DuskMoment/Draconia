#include "Sprite.h"

//when creating a custom hit box keep in mind that the widthOffset and heighOffset must be negitive and will shrink it from left and right, offset X and offset Y will shrink the hit box from the top and bottem
Sprite::Sprite(GraphicsBuffer* pBuffer, const Vector2D& ulCorner, unsigned int width, unsigned int height, int widthOffset, int heightOffset, int offsetX, int offsetY)
{
	mpBuffer = pBuffer;
	mLoc = ulCorner;

	mWidth = width;
	mHeight = height;

	generateHitBox(widthOffset, heightOffset, offsetX, offsetY);

}

//implement me
Sprite::Sprite()
{
	mLoc = ZERO_VECTOR2D; 
	mWidth = 0;
	mHeight = 0;
}

//implement me
Sprite::~Sprite()
{
	
}

void Sprite::generateHitBox(int widthOffset, int heightOffset, int offsetX, int offsetY)
{
	

	//mWidthHit = center.getX() + offsetX;
//	mHeightHit = center.getY() + offsetY;

	mWidthHit = widthOffset;
	mHeightHit = heightOffset;

	mLocOffsetX = offsetX;
	mLocOffsetY = offsetY;
}
