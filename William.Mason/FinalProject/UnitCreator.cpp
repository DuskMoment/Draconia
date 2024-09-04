#pragma once

#include "UnitCreator.h"
#include "GraphicsBufferManager.h"
#include "Animation.h"
#include "UnitManager.h"
#include "Game.h"
#include "DataReader.h"

#include "Player.h"
#include "Boss.h"
#include "PlayerFireball.h"
#include "BossFireball.h"
#include "Tailwind.h"
#include "EventSystem.h"

#include "GameEvent.h"
#include "DiffucltyChangeEvent.h"

UnitCreator* UnitCreator::mpInstance = nullptr;

UnitCreator::UnitCreator(GraphicsBufferManager* pGBM, UnitManager* pUM, DataReader* pDR)
{
	if (mpInstance == nullptr)
	{
		mpInstance = this;
	}

	mpGraphicsBufferManager = pGBM;
	mpUnitManager = pUM;
	mpDataReader = pDR;

	init();
}

UnitCreator::~UnitCreator()
{
	cleanup();
}

void UnitCreator::createInstance(GraphicsBufferManager* pGBM, UnitManager* pUM, DataReader* pDR)
{
	if (mpInstance == nullptr)
	{
		mpInstance = new UnitCreator(pGBM, pUM, pDR);
	}
}

UnitCreator* UnitCreator::getInstance()
{
	return mpInstance;
}

void UnitCreator::deleteInstance()
{
	if (mpInstance != nullptr)
	{
		delete mpInstance;
	}
	mpInstance = nullptr;
}

void UnitCreator::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == DIFFICULTY_CHANGE_EVENT)
	{
		const DiffucltyChangeEvent& changePoints = static_cast<const DiffucltyChangeEvent&>(theEvent);

		mpDifficulty = changePoints.getDifficulty();

		std::cout << "Changing Diff " << mpDifficulty << std::endl;
	}
}

void UnitCreator::init()
{
	loadAnim("glowing-balls", M_ASSET_PATH + "glowing-balls.png", M_SPRITES_DOWN, M_SPRITES_ACROSS, M_RED_SPRITE_OFFSET_X, M_RED_SPRITE_OFFSET_Y, 
		M_PIXEL_WIDTH, M_PIXEL_HEIGHT, mRedBallSpriteVec, mpRedBallAnimation);

	loadAnim("dragonchat", M_MYASSETS_PATH + M_DRAGON_TALK_PATH, 1, 4, 0, 0, 50, 50, mDragonChatVec, mpDragonChat, 5);
	loadAnim("behemothchat", M_MYASSETS_PATH + M_BEHEMOTH_TALK_PATH, 1, 4, 0, 0, 50, 50, mBehemothChatVec, mpBehemothChat, 5);

	loadAnim("reddragon", M_MYASSETS_PATH + M_DRAGON_PATH, 2, 4, 0, 0, 205, 161, mDragonSpriteVec, mpDragonAnimation, FRAMES_15, -20, -20, 10, 10);

	loadAnim("fireball", M_MYASSETS_PATH + M_FIREBALL_PATH, 2, 2, 0, 0, 128, 128, mFireballSpriteVec, mpFireballAnimation, FRAMES_15, 0, -40, 0, 20);
	loadAnim("bossfireball", M_MYASSETS_PATH + M_BOSS_FIREBALL_PATH, 2, 2, 0, 0, 128, 128, mBossFireballSpriteVec, mpBossFireballAnimation, FRAMES_15, 0, -40, 0, 20); // 

	loadAnim("behemoth", M_MYASSETS_PATH + M_BEHEMOTH_PATH, 1, 4, 0, 0, 196, 180, mBehemothFlyVec, mpBehemothFlyAnimation, FRAMES_15, 0, 300, 0, -150);

	loadAnim("tailwind", M_MYASSETS_PATH + M_TAILWIND_PATH, 1, 3, 0, 0, 96, 50, mTailwindVec, mpTailwindAnimation, FRAMES_15, 50, 50, -25, -25); // , 50, 50, -25, -25

	mAnimationsVec.push_back(*mpFireballAnimation);
	mBossFireballVec.push_back(*mpBossFireballAnimation);

	mDragonAnimsVec.push_back(*mpDragonAnimation);
	mDragonAnimsVec.push_back(*mpRedBallAnimation);

	mBenemothAnimsVec.push_back(*mpBehemothFlyAnimation);

	mTailwindAnimsVec.push_back(*mpTailwindAnimation);

	mChatAnimsVec.push_back(*mpDragonChat);
	mChatAnimsVec.push_back(*mpBehemothChat);

	BOSS_BULLET_SPEED_SLOW = mpDataReader->findIntDataByKey("bossBulletSpeedSlow");
	BOSS_BULLET_SPEED_MEDIUM = mpDataReader->findIntDataByKey("bossBulletSpeedMedium");
	BOSS_BULLET_SPEED_FAST = mpDataReader->findIntDataByKey("bossBulletSpeedFast");

	mBossPatternAXStart = mpDataReader->findIntDataByKey("bossPatternAXStart");
	mBossPatternAXEnd = mpDataReader->findIntDataByKey("bossPatternAXEnd");
	mBossPatternAXDiff = mpDataReader->findIntDataByKey("bossPatternAXDiff");
	mBossPatternAXStep = mpDataReader->findIntDataByKey("bossPatternAXStep");
	mBossPatternAYStart = mpDataReader->findIntDataByKey("bossPatternAYStart");
	mBossPatternAYEnd = mpDataReader->findIntDataByKey("bossPatternAYEnd");
	mBossPatternAYDiff = mpDataReader->findIntDataByKey("bossPatternAYDiff");
	mBossPatternAYGap = mpDataReader->findIntDataByKey("bossPatternAYGap");
	mBossPatternATailwindX = mpDataReader->findIntDataByKey("bossPatternATailwindX");
	mBossPatternATailwindY = mpDataReader->findIntDataByKey("bossPatternATailwindY");

	mBossPatternBXStart = mpDataReader->findIntDataByKey("bossPatternBXStart");
	mBossPatternBXEnd = mpDataReader->findIntDataByKey("bossPatternBXEnd");
	mBossPatternBXDiff = mpDataReader->findIntDataByKey("bossPatternBXDiff");
	mBossPatternBYStart = mpDataReader->findIntDataByKey("bossPatternBYStart");
	mBossPatternBYEnd = mpDataReader->findIntDataByKey("bossPatternBYEnd");
	mBossPatternBYDiff = mpDataReader->findIntDataByKey("bossPatternBYDiff");
	mBossPatternBTicks = mpDataReader->findIntDataByKey("bossPatternBTicks");

	mBossPatternCXStart = mpDataReader->findIntDataByKey("bossPatternCXStart");
	mBossPatternCXEnd = mpDataReader->findIntDataByKey("bossPatternCXEnd");
	mBossPatternCXDiff = mpDataReader->findIntDataByKey("bossPatternCXDiff");
	mBossPatternCYStart = mpDataReader->findIntDataByKey("bossPatternCYStart");
	mBossPatternCYEnd = mpDataReader->findIntDataByKey("bossPatternCYEnd");
	mBossPatternCYDiff = mpDataReader->findIntDataByKey("bossPatternCYDiff");
	mBossPatternCLineDiff = mpDataReader->findIntDataByKey("bossPatternCLineDiff");
	mBossPatternCLineLengths = mpDataReader->findIntDataByKey("bossPatternCLineLengths");
	mBossPatternCLineSkip = mpDataReader->findIntDataByKey("bossPatternCLineSkip");
	mBossPatternCLineGap = mpDataReader->findIntDataByKey("bossPatternCLineGap");
	mBossPatternCLineX = mpDataReader->findIntDataByKey("bossPatternCLineX");

	mBossRandomYMin = mpDataReader->findIntDataByKey("bossRandomYMin");
	mBossRandomYRange = mpDataReader->findIntDataByKey("bossRandomYRange");
	mBossRandomX = mpDataReader->findIntDataByKey("bossRandomX");

	EventSystem::getInstance()->addListener((EventType)DIFFICULTY_CHANGE_EVENT, this);
}

void UnitCreator::cleanup()
{
	//other classes
	delete mpRedBallAnimation;
	mpRedBallAnimation = nullptr;

	delete mpBlueBallAnimation;
	mpBlueBallAnimation = nullptr;

	delete mpDragonAnimation;
	mpDragonAnimation = nullptr;

	delete mpFireballAnimation;
	mpFireballAnimation = nullptr;

	delete mpBehemothFlyAnimation;
	mpBehemothFlyAnimation = nullptr;

	delete mpTailwindAnimation;
	mpTailwindAnimation = nullptr;

	delete mpBossFireballAnimation;
	mpBossFireballAnimation = nullptr;

	delete mpDragonChat;
	mpDragonChat = nullptr;

	delete mpBehemothChat;
	mpBehemothChat = nullptr;

	mAnimationsVec.clear();
	mBossFireballVec.clear();
	mDragonAnimsVec.clear();
	mBenemothAnimsVec.clear();
	mTailwindAnimsVec.clear();
	mChatAnimsVec.clear();
}

void UnitCreator::loadAnim(std::string bufferKey, std::string assetPath, int spritesDown, 
	int spritesAcross, int offsetX, int offsetY, int pixelWidth, int pixelHeight, std::vector<Sprite>& vec, Animation*& anim, 
	int frames, int widthOffset, int heightOffset, int hitboxOffsetX, int hitboxOffsetY)
{
	mpGraphicsBufferManager->createBuffer(bufferKey, assetPath);

	for (unsigned int y = 0; y < (unsigned int)spritesDown; y++)
	{
		for (unsigned int x = 0; x < (unsigned int)spritesAcross; x++)
		{
			GraphicsBuffer* pTarget = mpGraphicsBufferManager->getBuffer(bufferKey);
			Sprite sprite(pTarget, Vector2D(
				(int)((x + offsetX) * pixelWidth),
				(int)((y + offsetY) * pixelHeight)),
				pixelWidth, pixelHeight, widthOffset, heightOffset, hitboxOffsetX, hitboxOffsetY);
			vec.push_back(sprite);
		}
	}
	anim = new Animation(vec, frames, true); 
}

void UnitCreator::createStartingEntities()
{
	/*pPlayer = new Player(Vector2D(400, 300), mDragonAnimsVec, Vector2D(0, 0), 0);
	pUnitManager->addUnit(pPlayer);*/

	createPlayer(Vector2D(400, 300), Vector2D(0, 0), 0);
	
	createBoss(Vector2D(600, 300), Vector2D(0, 0), 0);

	createHUDUnits();
}

void UnitCreator::createHUDUnits()
{
	mpChat = new Unit(Vector2D(000, 500), mChatAnimsVec, Vector2D(0, 0), 0);
	mpUnitManager->addUnit(mpChat);

	Game::getInstance()->renderUnitInHUD(mpChat);
}

Player* UnitCreator::createPlayer(Vector2D loc, Vector2D vel, int speed)
{
	mpPlayer = new Player(loc, mDragonAnimsVec, vel, speed, mpDataReader);
	mpUnitManager->addUnit(mpPlayer);

	return mpPlayer;
}

Boss* UnitCreator::createBoss(Vector2D loc, Vector2D vel, int speed)
{
	mpBoss = new Boss(loc, mBenemothAnimsVec, vel , speed, mpDataReader);
	mpUnitManager->addUnit(mpBoss);

	return mpBoss;
}


void UnitCreator::createPlayerFireball(float size, Vector2D loc )
{
	/*PlayerFireball* fireball = new PlayerFireball(pPlayer->projectileSpawnLocation(), mAnimationsVec, Vector2D(100, 0), 100, size);
	pUnitManager->addUnit(fireball);*/

	mpUnitManager->addUnit(new PlayerFireball(loc == Vector2D(0,0) ? mpPlayer->projectileSpawnLocation() : loc, mAnimationsVec, Vector2D(100, 0), 2, size));
}


void UnitCreator::createBossPatternA()
{
	int yStart = mBossPatternAYStart;
	int yEnd = mBossPatternAYEnd;

	int flip = 1;
	int ticks = 0;
	for (int x = mBossPatternAXStart; x <= mBossPatternAXEnd; x += mBossPatternAXDiff)
	{
		for (int y = yStart; y > yEnd; y -= mBossPatternAYDiff)
		{
			mpUnitManager->createFireball(Vector2D(x, y), mBossFireballVec, Vector2D(150, 0), BOSS_BULLET_SPEED_MEDIUM * mpDifficulty, 0.5);
			x += mBossPatternAXStep;
			ticks++;
		}

		yStart += mBossPatternAYGap * flip;
		yEnd += mBossPatternAYGap * flip;


		mpUnitManager->addUnit(new Tailwind(Vector2D(mBossPatternATailwindX + x, mBossPatternATailwindY + yEnd), mTailwindAnimsVec, Vector2D(150, 0), BOSS_BULLET_SPEED_MEDIUM * mpDifficulty, mpDataReader));

		flip *= -1;

		x += flip == -1 ? 0 : ticks*mBossPatternAXStep;
		ticks = 0;
	}
}

void UnitCreator::createBossPatternB()
{
	int yStart = mBossPatternBYStart;
	int yEnd = mBossPatternBYEnd;

	int ticks = 0;
	int dir = 1;

	for (int x = mBossPatternBXStart; x <= mBossPatternBXEnd; x += mBossPatternBXDiff)
	{
		for (int y = yStart; y <= yEnd; y += mBossPatternBYDiff)
		{
			mpUnitManager->createFireball(Vector2D(x, y), mBossFireballVec, Vector2D(150, 0), BOSS_BULLET_SPEED_FAST * mpDifficulty, 0.5);
		}

		if (ticks > mBossPatternBTicks || ticks < -mBossPatternBTicks)
		{
			ticks = 0;
			dir *= -1;
		}
		yStart += ticks * ticks * dir;
		yEnd += ticks * ticks * dir;

		ticks+= dir;
	}
}

void UnitCreator::createBossPatternC()
{
	int yStart = mBossPatternCYStart;
	int yEnd = mBossPatternCYEnd;

	Tailwind* tailwind;

	for (int y = yStart; y <= yEnd; y += mBossPatternCYDiff)
	{
		for (int x = mBossPatternCXStart; x <= mBossPatternCXEnd; x += mBossPatternCXDiff)
		{
			mpUnitManager->createFireball(Vector2D(x, y), mBossFireballVec, Vector2D(100, 0), BOSS_BULLET_SPEED_MEDIUM * mpDifficulty, 0.5);
		}

		tailwind = new Tailwind(Vector2D(mBossPatternCXStart, y), mTailwindAnimsVec, Vector2D(100, 0), BOSS_BULLET_SPEED_MEDIUM * mpDifficulty, mpDataReader);
		mpUnitManager->addUnit(tailwind);
	}

	for (int y = yStart; y <= yEnd; y += mBossPatternCLineDiff)
	{
		if (y % mBossPatternCLineLengths == mBossPatternCLineSkip)
		{
			y += mBossPatternCLineGap;
		}

		mpUnitManager->createFireball(Vector2D(mBossPatternCLineX, y), mBossFireballVec, Vector2D(150, 0), BOSS_BULLET_SPEED_FAST * mpDifficulty, 0.5);
	}
}

void UnitCreator::createBossFireBall(Vector2D loc, Vector2D vel, int speed)
{
	mpUnitManager->createFireball(loc, mBossFireballVec,vel, speed, 0.5);
}

void UnitCreator::createRandomBossFireball()
{
	int randY = rand() % mBossRandomYRange + mBossRandomYMin;
	mpUnitManager->createFireball(Vector2D(mBossRandomX, randY), mBossFireballVec, Vector2D(100, 0),BOSS_BULLET_SPEED_SLOW * mpDifficulty, 0.5);
}

void UnitCreator::createTailwind()
{
	Tailwind* tailwind = new Tailwind(mpBoss->getLoc(), mTailwindAnimsVec, Vector2D(100, 0), 100, mpDataReader);
	mpUnitManager->addUnit(tailwind);
}

void UnitCreator::createTailwind(Vector2D loc, Vector2D vel, int speed)
{
	Tailwind* tailwind = new Tailwind(loc, mTailwindAnimsVec, vel, speed, mpDataReader);
	mpUnitManager->addUnit(tailwind);
}