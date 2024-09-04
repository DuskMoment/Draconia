#pragma once
#include "Player.h"
#include <Animation.h>
#include <Sprite.h>
#include <GraphicsBuffer.h>
#include <GraphicsSystem.h>
#include "Game.h"
#include "UnitCreator.h"
#include "EventSystem.h"
#include "GameOverEvent.h"
#include "PlaySoundEvent.h"
#include "PlayerHealthEvent.h"
#include "DataReader.h"

Player::Player(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, DataReader* data):Unit(loc, animations, vel, speed)
{
	mDown = false;
	mLeft = false;
	mRight = false;
	mUp = false;
	mShoot = false;

	mTeam = 3;
	mTargetTeam = 4;
	mDeleteOffscreen = false;

	mSpeed = BASE_SPEED;

	mUnitSize = 0.5f;

	BASE_HEALTH = data->findIntDataByKey("playerHealth");

	mHealth = BASE_HEALTH;

	PlayerHealthEvent event(mHealth);
	EventSystem::getInstance()->fireEvent(event);
}
//
Player::~Player()
{
	std::cout << "player being deleted!!";
}

void Player::update(float deltaTime)
{
	mSpeed -= (SPEED_DECAY * (deltaTime / 1000));
	if (mSpeed < BASE_SPEED)
		mSpeed = BASE_SPEED;

	//std::cout << "mvel is " << mVel.getX() << " " << mVel.getY() << std::endl;
	mLoc += mVel * (deltaTime / 1000) * mSpeed;
	// cout << "mloc is " << mLoc.getX() << " " << mLoc.getY() << endl;

	if (mShouldAnimate)
	{
		mAnimationVec.at(mAnimationIndex).update(deltaTime);
	}

	if (mShoot)
	{
		mChargeTime += (deltaTime / 1000);
	}
}

void Player::setVelocity(Vector2D vel)
{
	mVel = vel;
}

void Player::setInput(Input dir, bool val)
{
	mLastShoot = mShoot;

	switch (dir)
	{
	case Up:
		mUp = val;
		break;
	case Down:
		mDown = val;
		break;
	case Right:
		mRight = val;
		break;
	case Left:
		mLeft = val;
		break;
	case Shoot:
		mShoot = val;
		break;
	}

	Vector2D vec(mRight ? 100 : 0 + mLeft ? -100 : 0, mUp ? -100 : 0 + mDown ? 100 : 0);

	//cout << "X is " << vec.getX() << " " << vec.getY();
	setVelocity(vec);

	if (mLastShoot && !mShoot)
	{

		if (mChargeTime < FIREBALL_MIN_CHARGE_TIME)
			mChargeTime = FIREBALL_MIN_CHARGE_TIME;

		if (mChargeTime > FIREBALL_MAX_CHARGE_TIME)
			mChargeTime = FIREBALL_MAX_CHARGE_TIME;

		if (mChargeTime > FIREBALL_MAX_CHARGE_TIME / 2)
			EventSystem::getInstance()->fireEvent(PlaySoundEvent("fireballLarge"));
		else
			EventSystem::getInstance()->fireEvent(PlaySoundEvent("fireballSmall"));
			

		UnitCreator::getInstance()->createPlayerFireball(mChargeTime * FIREBALL_BASE_SIZE_MODIFIER);
	}
	else if (!mLastShoot && mShoot)
	{
		mChargeTime = 0;
		EventSystem::getInstance()->fireEvent(PlaySoundEvent("charge"));
	}
}

bool Player::myCollision(Unit* other)
{
	return false;
}

bool Player::theirCollision(Unit* other)
{
	// generally speaking we will not use this function in favor 
	// of casting to the player in their my collision when objects collide with it
	return false;
}

void Player::takeDamage(int value)
{
	mHealth -= value;
	if (value > 0)
	{
		EventSystem::getInstance()->fireEvent(PlaySoundEvent("playerDamage"));
	}
	
	EventSystem::getInstance()->fireEvent(PlayerHealthEvent(mHealth));

	if (mHealth <= 0)
	{
		// end game event
		GameOverEvent over;
		EventSystem::getInstance()->fireEvent(over);
	}
}

void Player::applyTailwind(float value)
{
	std::cout << "tailwind collision!";
	mSpeed += value;
	if (mSpeed > MAX_SPEED)
	{
		mSpeed = MAX_SPEED;
	}
}
