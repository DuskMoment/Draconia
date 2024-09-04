#include "PlayerFireball.h"
#include <Animation.h>
#include <Sprite.h>
#include <GraphicsBuffer.h>
#include <GraphicsSystem.h>
#include "Game.h"
#include "EventSystem.h"
#include "PlaySoundEvent.h"

PlayerFireball::PlayerFireball(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, float size) : Unit(loc, animations, vel, speed)
{
	mDeleteOffscreen = true;
	mUnitSize = size;

	mLoc = Vector2D(loc.getX(), loc.getY() - getWidthAndHeight().getY() / 2);
	mVel = Vector2D(vel.getX() * size, vel.getY() * size);
	mBulletDamage = size;
}

PlayerFireball::~PlayerFireball()
{
	std::cout << "Base called" << std::endl;
}


void PlayerFireball::update(float deltaTime)
{
	mLoc += mVel * (deltaTime / 1000) * mSpeed;
	if (mShouldAnimate)
	{
		mAnimationVec.at(mAnimationIndex).update(deltaTime);
	}
}

bool PlayerFireball::myCollision(Unit* other)
{
	EventSystem::getInstance()->fireEvent(PlaySoundEvent(mUnitSize > 0.5 ? "bossDamageHigh" : "bossDamageLow"));
	return true;
}

bool PlayerFireball::theirCollision(Unit* other)
{
	std::cout << "their collision!\n";

	return false;
}