#pragma once
#include "Unit.h"
#include <Animation.h>
#include <Sprite.h>
#include <GraphicsBuffer.h>
#include <GraphicsSystem.h>


Unit::Unit(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, bool pooled)
{
	mLoc = loc;
	mAnimationVec = animations;
	mAnimationIndex = 0;

	mVel = vel;
	mSpeed = speed;
	mVel.normalize();

	mPooledObject = pooled;
}

Unit::~Unit()
{
	//owns nothing
	//std::cout << "unit deletion!!";
}

void Unit::update(float deltaTime)
{
	mLoc += mVel * (deltaTime / 1000) * mSpeed;
	if (mShouldAnimate)
	{
		mAnimationVec.at(mAnimationIndex).update(deltaTime);
	}
}

void Unit::addAnimation(const Animation& newAnimaiton)
{
	mAnimationVec.push_back(newAnimaiton);
}

void Unit::setPosition(const Vector2D& newLoc)
{
	mLoc = newLoc;
}

void Unit::draw()
{
	if (mRenderInHUD)
		return;

	float offSetX = mAnimationVec.at(mAnimationIndex).getCurrentSprite().getWidth();
	float offSetY = mAnimationVec.at(mAnimationIndex).getCurrentSprite().getHeight();

	offSetX = offSetX / 2;
	offSetY = offSetY / 2;

	Vector2D offSet(offSetX, offSetY);

	GraphicsSystem::getBackBuffer()->draw(mLoc-offSet, 
		mAnimationVec.at(mAnimationIndex).getCurrentSprite(), mUnitSize);
}

void Unit::setAnimationByIndex(int newIndex)
{
	if ((unsigned int) newIndex < mAnimationVec.size())
	{
		mAnimationIndex = newIndex;
	}
	
}

void Unit::changeAnimationTime(float newTime)
{
	mAnimationVec.at(mAnimationIndex).setSpeed(newTime);
}

Animation* Unit::getCurrentAnimation()
{
	return &mAnimationVec.at(mAnimationIndex);
}

Vector2D Unit::getWidthAndHeight()
{
	Vector2D size = ZERO_VECTOR2D;

 	int width = mAnimationVec.at(mAnimationIndex).getCurrentSprite().getWidth();
	size.setX(width * mUnitSize);

	int height = mAnimationVec.at(mAnimationIndex).getCurrentSprite().getHeight();
	size.setY(height * mUnitSize);

	return size;
}

bool Unit::collidedWithMouse(Vector2D loc)
{
	//gets half width and hight 
	Vector2D size = getWidthAndHeight();
		//Vector2D unitLoc = mpUnitVec.at(i)->getLocation();
		//two x pos and two y pos top left is negitive 

	float width = size.getX();
	float height = size.getY();

	Vector2D ul = mLoc - (size/2);
	if (loc.getX() < ul.getX())
	{
		return false;
	}
	if (loc.getX() > ul.getX() + width)
	{
		return false;
	}
	if (loc.getY() < ul.getY())
	{
		return false;
	}
	if (loc.getY() > ul.getY() + height)
	{
		return false;
	}
	return true;
}

bool Unit::OnScreen()
{
	float width = GraphicsSystem::getBackBuffer()->getWidth();
	float height = GraphicsSystem::getBackBuffer()->getHeight();

	Vector2D spriteSize = getWidthAndHeight();

	Vector2D size(width, height);

	Vector2D ul(0, 0);

	if (mLoc.getX() <= ul.getX() - spriteSize.getX())
	{
		return false;
	}
	// commenting the check for the far right of the screen so we can spawn projectiles on the other side
	//if (mLoc.getX() > ul.getX() + width + spriteSize.getX())
	//{
	//	return false;
	//}
	if (mLoc.getY() < ul.getY() - spriteSize.getY())
	{
		return false;
	}
	if (mLoc.getY() > ul.getY() + height + spriteSize.getY())
	{
		return false;
	}
	//std::cout << "on screen" << std::endl;
	return true;
}
	

void Unit::shouldAnimate(bool shouldAnimate)
{
	mShouldAnimate = shouldAnimate;
}

bool Unit::myCollision(Unit* other)
{
	return true;
}

bool Unit::theirCollision(Unit* other)
{
	return false;
}
