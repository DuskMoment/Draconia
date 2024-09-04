#include "UnitManager.h"
#include "Unit.h"
#include <Animation.h>
#include <GraphicsBufferManager.h>
#include <Vector2D.h>
#include <EventSystem.h>
#include "DataReader.h"
#include "ChangePointEvent.h"
#include "PlaySoundEvent.h"
#include "PlayerFireball.h"
#include "BossFireball.h"

UnitManager::UnitManager(int poolSize)
	:mPool(poolSize, sizeof(BossFireball))
{
}

UnitManager::~UnitManager()
{
	cleanup();
}

void UnitManager::cleanup()
{
	for (unsigned int i = 0; i < mpUnitVec.size(); i++)
	{
		if (!mpUnitVec.at(i)->mPooledObject)
		{
			Unit* target = mpUnitVec.at(i);
			delete target;
		}
		else
		{
			BossFireball* target = (BossFireball*)mpUnitVec.at(i);

			target->~BossFireball();
			mPool.freeObject((Byte*)target);

		}
		
	}
	mpUnitVec.clear();

	mSpawnChance = mDefaultSpawnChance;

	std::cout <<"Pooled objects " << mPool.getNumFreeObjects() << std::endl;

	
}

bool UnitManager::init(const DataReader* dataReader, int poolSize)
{
	mpDataReader = dataReader;

	mDefaultSpawnChance = mpDataReader->findIntDataByKey("spawnChance");
	mSpawnChance = mDefaultSpawnChance;
	mTimeTillIncrease = mpDataReader->findIntDataByKey("timeTillIncrease");
	mSpeedIncreaseAmmount = mpDataReader->findIntDataByKey("speedIncreaseAmmount");

	
	return true;
}

void UnitManager::addUnit(Unit* pUnit)
{
	mpUnitVec.push_back(pUnit);
}

void UnitManager::createUnit(std::vector<Animation> animation, Vector2D loc, int highVel, int lowVel, int highSpeed, int lowSpeed)
{
	int range = (highVel - lowVel) + 1;
	int x = rand() % range + lowVel;
	int y = 0; // rand() % range + lowVel;
	Vector2D vel(x, y);
	range = (highSpeed - lowSpeed) + 1;
	int speed = rand() % range + mSpeedMod + lowSpeed;



	Unit* pNewUnit = new Unit(loc, animation, vel, speed);
	if (!mShouldAnimate)
	{
		pNewUnit->shouldAnimate(false);
	}
	mpUnitVec.push_back(pNewUnit);
}

void UnitManager::createFireball(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, float size)
{
	//take from meme poll
	 //std::cout << "THIS IS THE POOLED OBJECTs BEFROE " << mPool.getNumFreeObjects() << std::endl;
	 Byte* ptr = mPool.allocateObject();
	 //std::cout << "THIS IS THE POOLED OBJECTs AFTER " << mPool.getNumFreeObjects() << std::endl;
	 
	
	 if (ptr != NULL)
	 {
		 //std::cout << "MAKING A UNIT" << endl;
		 BossFireball* pFireBall = new (ptr)BossFireball(loc, animations, vel, speed, size);
		 pFireBall->mPooledObject = true;

		 addUnit(pFireBall);
	 }

	//if no memeory do notinhg
	 // perhaps we delete last unit instead?
}

void UnitManager::destroyUnit(Unit* pUnit)
{
	for (unsigned int i = 0; i < mpUnitVec.size(); i++)
	{
		Unit* pTarget = mpUnitVec.at(i);
		if (pTarget == pUnit)
		{
			if (!pTarget->mPooledObject)
			{
				delete pUnit;
			}
			else
				//frees memeory if pooled object
			{
				//evil casting >:)
				PlayerFireball* fireBallptr = (PlayerFireball*)pTarget;

				fireBallptr->~PlayerFireball();
				mPool.freeObject((Byte*)fireBallptr);

				//std::cout << "POOLED OBJECTS AFTER DESTRUCTION " << mPool.getNumFreeObjects() << std::endl;
			}
			mpUnitVec.erase(mpUnitVec.begin() + i);
			
			break;
		}
	}
}

void UnitManager::destroyUnitAtLocation(Vector2D loc)
{
	//loc of the unit and width and height
	//check it against the mosue location


	for (unsigned int i = 0; i < mpUnitVec.size(); i++)
	{
		if (mpUnitVec.at(i)->collidedWithMouse(loc))
		{
			destroyUnit(mpUnitVec.at(i));
		}
	}

	/*std::vector<int> destroyIndex;

	for (unsigned int i = 0; i < mpUnitVec.size(); i++)
	{
		if (mpUnitVec.at(i)->collidedWithMouse(loc))
		{
			destroyIndex.push_back(i);
		}
	}

	for (unsigned int i = 0; i < destroyIndex.size(); i++)
	{
		if ((unsigned int)destroyIndex.at(i) < mpUnitVec.size())
		{
			destroyUnit(mpUnitVec.at(destroyIndex.at(i)));
		}

	}*/
}

void UnitManager::changeAnimationAtLocation(Vector2D loc)
{
	for (unsigned int i = 0; i < mpUnitVec.size(); i++)
	{
		if (mpUnitVec.at(i)->collidedWithMouse(loc))
		{

			if (mpUnitVec.at(i) != nullptr)
			{
				int currentIndex = mpUnitVec.at(i)->getAnimationIndex();
				if (currentIndex == 0)
				{
					mpUnitVec.at(i)->setAnimationByIndex(1);
				}
				else
				{
					mpUnitVec.at(i)->setAnimationByIndex(0);
				}
			}
		}
	}
}

void UnitManager::increaseSpeed(float deltaTime)
{
	
	if (mSpeedIncreseTimer * 0.001 > mTimeTillIncrease)
	{
		//plus an ammout to a modifyer
		changeSpeedMod(mSpeedMod + mSpeedIncreaseAmmount);
		mSpeedIncreseTimer = 0;
		
	}
	else
	{
		mSpeedIncreseTimer += deltaTime;

	}
}

Unit* UnitManager::getUnit()
{
	if (mpUnitVec.size() > 0)
	{
		return mpUnitVec.at(mpUnitVec.size() - 1);
	}
	else
	{
		return nullptr;
	}

}

void UnitManager::animate(bool animating)
{
	mShouldAnimate = animating;
	for (unsigned int i = 0; i < mpUnitVec.size(); i++)
	{
		mpUnitVec.at(i)->shouldAnimate(mShouldAnimate);
	}
}

void UnitManager::update(float deltaTime)
{
	

	for (unsigned int i = 0; i < mpUnitVec.size(); i++)
	{ 
		
		mpUnitVec.at(i)->update(deltaTime);
		
		checkCollisions(mpUnitVec.at(i));

		if (!mpUnitVec.at(i)->OnScreen() && mpUnitVec.at(i)->mDeleteOffscreen)
		{
			//send a change point event
			bool negative;

			if (mpUnitVec.at(i)->getAnimationIndex() == 0)
			{
				negative = true;
			}
			else
			{
				negative = false;
			}

			
			mpUnitsToDestroyVec.push_back(mpUnitVec.at(i));

			ChangePointEvent changePointEvent(negative);
			EventSystem::getInstance()->fireEvent(changePointEvent);
			
		}
	}
	
	for (unsigned int i = 0; i < mpUnitsToDestroyVec.size(); i++)
	{
		destroyUnit(mpUnitsToDestroyVec.at(i));
	}

	mpUnitsToDestroyVec.clear();

	increaseSpeed(deltaTime);
}

void UnitManager::draw()
{
	for (unsigned int i = 0; i < mpUnitVec.size(); i++)
	{
		mpUnitVec.at(i)->draw();
	}
}

void UnitManager::checkCollisions(Unit* pUnit)
{
	Vector2D mySize = pUnit->getHitboxWidthHeight(); 
	Vector2D mLoc = pUnit->getHitboxLoc();

	Vector2D theirSize;
	Vector2D theirLoc;

	for (unsigned int i = 0; i < mpUnitVec.size(); i++)
	{
		Unit* pTarget = mpUnitVec.at(i);

		//std::cout << "team 1 is " << pTarget->mTeam << " team 2 is " << mTargetTeam << std::endl;

		if (pTarget->mTeam == pUnit->mTargetTeam)
		{
			theirSize = pTarget->getHitboxWidthHeight();
			theirLoc = pTarget->getHitboxLoc();

			// so this is checking if this unit's location is colliding with the box size/location of the other unit
			// got this formula from https://happycoding.io/tutorials/processing/collision-detection#rectangle-rectangle-collision-detection 
			if (mLoc.getX() + mySize.getX() > theirLoc.getX()
				&& mLoc.getX() < theirLoc.getX() + theirSize.getX()
				&& mLoc.getY() + mySize.getY() > theirLoc.getY()
				&& mLoc.getY() < theirLoc.getY() + theirSize.getY())
			{
				//std::cout << "collision found! ptarget's team is " << pTarget->mTeam << " and punit's target is " << pUnit->mTargetTeam;
				// execute collision here;
				bool selfDestruct;

				// there's some funky in-script shorthand for this that i wish i knew 
				// like putting a function in as a variable to a function

				selfDestruct = pTarget->theirCollision(pUnit);
				if (selfDestruct)
				{
					mpUnitsToDestroyVec.push_back(pTarget);
				}

				selfDestruct = pUnit->myCollision(pTarget);
				if (selfDestruct)
				{
					mpUnitsToDestroyVec.push_back(pUnit);
				}
			}
		}
	}
}


