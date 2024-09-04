#include "BossFireball.h"
#include <Animation.h>
#include <Sprite.h>
#include <GraphicsBuffer.h>
#include <GraphicsSystem.h>
#include "Game.h"
#include "Player.h"

BossFireball::BossFireball(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, float size) : Unit(loc, animations, vel, speed)
{
	mDeleteOffscreen = true;
	mUnitSize = size;

	mLoc = Vector2D(loc.getX(), loc.getY() - getWidthAndHeight().getY() / 2);
	//mVel = Vector2D(vel.getX() * size, vel.getY() * size);
	mBulletDamage = size;

	mTargetTeam = 3;
}

BossFireball::~BossFireball()
{
	std::cout << "Base called" << std::endl;
}


void BossFireball::update(float deltaTime)
{
	mLoc -= mVel * (deltaTime / 1000) * mSpeed;
	if (mShouldAnimate)
	{
		mAnimationVec.at(mAnimationIndex).update(deltaTime);
	}
}

bool BossFireball::myCollision(Unit* other)
{
	Player* playerptr = (Player*)other;
	playerptr->takeDamage(1);

	return true;
}

bool BossFireball::theirCollision(Unit* other)
{
	std::cout << "their collision!\n";

	return false;
}