#pragma once
#include <Trackable.h>
#include <Vector2D.h>
#include "Animation.h"
#include "Game.h"
#include "Player.h"
#include "EventSystem.h"
#include "PlaySoundEvent.h"
#include "DataReader.h"

#include "Tailwind.h"

Tailwind::Tailwind(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, DataReader* data) : Unit(loc, animations, vel, speed)
{
	mDeleteOffscreen = true;
	mTargetTeam = 3;

	mUnitSize = 1;

	TAILWIND_HEAL = data->findIntDataByKey("tailwindHeal");
	TAILWIND_OVERHEAL = data->findIntDataByKey("tailwindOverheal");
}

void Tailwind::update(float deltaTime)
{
	mLoc -= mVel * (deltaTime / 1000) * mSpeed;
	if (mShouldAnimate)
	{
		mAnimationVec.at(mAnimationIndex).update(deltaTime);
	}
}

bool Tailwind::myCollision(Unit* other)
{
	Player* playerptr = (Player*)other;
	playerptr->applyTailwind(TAILWIND_SPEED);
	

	std::cout << "TAILWIND!";
	if (!tailwindUsed)
	{
		tailwindUsed = true;
		EventSystem::getInstance()->fireEvent(PlaySoundEvent("tailwind"));
		playerptr->takeDamage(-1 * (playerptr->isAboveMaxHealth() ? TAILWIND_OVERHEAL : TAILWIND_HEAL));
	}

	return false;
}

bool Tailwind::theirCollision(Unit* other)
{
	std::cout << "their collision!\n";

	return false;
}