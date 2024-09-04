#pragma once
#include "Boss.h"
#include <Animation.h>
#include <Sprite.h>
#include <GraphicsBuffer.h>
#include <GraphicsSystem.h>
#include "Game.h"
#include "UnitCreator.h"
#include "DataReader.h"

#include "EventSystem.h"
#include "BossHealthEvent.h"
#include "GameOverEvent.h"

#include "PlayerFireball.h"

Boss::Boss(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, DataReader* data) :Unit(loc, animations, vel, speed)
{
	mTeam = 2;
	mTargetTeam = 1;

	BASE_HEALTH = data->findIntDataByKey("bossHealth");
	TIME_BETWEEN_PATTERNS = data->findIntDataByKey("timeBetweenPatterns");
	TIME_BEFORE_DOWNTIME = data->findIntDataByKey("timeBeforeDowntime");

	mBossHealth = BASE_HEALTH;

	mDeleteOffscreen = false;

	mUnitSize = 1.7f;

	pEventSystem = EventSystem::getInstance();

	//update HUD and UI
	BossHealthEvent event(mBossHealth);
	pEventSystem->fireEvent(event);
}

void Boss::update(float deltaTime)
{
	mLoc += mVel * (deltaTime / 1000);
	if (mShouldAnimate)
	{
		mAnimationVec.at(mAnimationIndex).update(deltaTime);
	}

	int chance = rand();

	mSinceLastPattern += (deltaTime / 1000);

	if (mSinceLastPattern >= TIME_BETWEEN_PATTERNS)
	{
		cout << "NEW PATTERN" << endl;

		mSinceLastPattern = 0;

		switch (chance % 3)
		{
		case 0:
			UnitCreator::getInstance()->createBossPatternA();
			break;
		case 1:
			UnitCreator::getInstance()->createBossPatternB();
			break;
		case 2:
			UnitCreator::getInstance()->createBossPatternC();
			break;
		default:
			break;
		}
	}
	else if (mSinceLastPattern >= TIME_BEFORE_DOWNTIME)
	{
		if (chance % 10 == 0)
		{
			UnitCreator::getInstance()->createRandomBossFireball();
		}
	}

}

bool Boss::myCollision(Unit* other)
{
	return false;
}

bool Boss::theirCollision(Unit* other)
{
	std::cout << "their collision!\n";
	//if (mAnimationIndex == 0)
	//{
	//	setAnimationByIndex(1);
	//}
	//else
	//{
	//	setAnimationByIndex(0);
	//}

	PlayerFireball* fb = static_cast<PlayerFireball*>(other);

	mBossHealth -= fb->getBulletDamage();

	TIME_BETWEEN_PATTERNS = (int)((mBossHealth / (BASE_HEALTH / DIFFICULTY_PHASES))) + TIME_BEFORE_DOWNTIME;

	//UnitCreator::getInstance()->createTailwind();

	//if (mBossHealth < (BASE_HEALTH / 2))
	//{
	//	
	//}

	//UnitCreator::getInstance()->createBossPatternC();

	BossHealthEvent health(mBossHealth);
	pEventSystem->fireEvent(health);

	if (mBossHealth < 0)
	{
		GameOverEvent over;
		EventSystem::getInstance()->fireEvent(over);
	}

	return mBossHealth < 0;
}

void Boss::setVelocity(Vector2D vel)
{
	mVel = vel;
	mSpeed = 3000;
}