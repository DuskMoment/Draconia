#pragma once
#include "HUD.h"
#include <GraphicsBuffer.h>
#include <Font.h>
#include <Color.h>
#include <Vector2D.h>
#include <GraphicsSystem.h>
#include "DataReader.h"
#include "GameEvent.h"
#include <EventSystem.h>
#include "Unit.h"

#include "ChangePointEvent.h"
#include "PlaySoundEvent.h"
#include "GameOverEvent.h"
#include "BossHealthEvent.h"
#include "ChangeLanguageEvent.h"
#include "PlayerHealthEvent.h"


HUD::HUD(GraphicsBufferManager* bufferManager, const DataReader* dataReader)
{
	mpBufferManager = bufferManager;
	mpDataReader = dataReader;

	mFPS = 0;
	mScore = 10;
	mPause = false;

	mNegPoints = mpDataReader->findIntDataByKey("negPoints");
	mPosPoints = mpDataReader->findIntDataByKey("posPoints");
	mDefualtScore = mpDataReader->findIntDataByKey("defaultScore");

	mBossBaseHealth = mpDataReader->findIntDataByKey("bossHealth");
	mBossHealth = mpDataReader->findIntDataByKey("bossHealth");

	mpColor = nullptr;
	mpFont = nullptr;

	string key = std::to_string(mCurrentLanguage) + "phase" + std::to_string(0);
	std::cout << key << endl;
	bossText = mpDataReader->findStringDataByKey(key);
}

HUD::~HUD()
{
	cleanup();
}

void HUD::init(int width, int height)
{
	EventSystem::getInstance()->addListener((EventType)CHANGE_POINT_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)BOSS_HEALTH_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAYER_HEALTH_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)CHANGE_LANGUAGE_EVENT, this);

	//load font 
	mpFont = new Font(ASSET_PATH + FONT_FILENAME, FONT_SIZE);
	mpFontSmall = new Font(ASSET_PATH + FONT_FILENAME, FONT_SIZE_SMALL);
	//white
	mpColor = new Color(1.0f, 1.0f, 1.0f);
	mpBufferManager->createBuffer("HUD", width, height, Color(1.0f,1.0f,1.0f));
}

void HUD::cleanup()
{
	delete mpFont;
	mpFont = nullptr;

	delete mpFontSmall;
	mpFontSmall = nullptr;

	delete mpColor;
	mpColor = nullptr;
}

void HUD::handleEvent(const Event& theEvent)
{
	if (theEvent.getType() == CHANGE_POINT_EVENT)
	{
		const ChangePointEvent& changePoints = static_cast<const ChangePointEvent&>(theEvent);

		if (changePoints.getIsNegitive())
		{
			mScore += mNegPoints;
		}
		else
		{
			mScore += mPosPoints;

		}
	}
	else if (theEvent.getType() == CHANGE_LANGUAGE_EVENT)
	{
		const ChangeLanguageEvent& newLang = static_cast<const ChangeLanguageEvent&>(theEvent);
		mCurrentLanguage = newLang.getLanguage();

		updateChat();
	}
	else if (theEvent.getType() == BOSS_HEALTH_EVENT)
	{
		const BossHealthEvent& health = static_cast<const BossHealthEvent&>(theEvent);

		mBossHealth = health.getHealth();

		updateChat();
	}
	else if (theEvent.getType() == PLAYER_HEALTH_EVENT)
	{
		const PlayerHealthEvent& health = static_cast<const PlayerHealthEvent&>(theEvent);

		mPlayerHealth = health.getHealth();

		updateChat();
	}
}

void HUD::updateChat()
{
	int phase = (int)(5 - (mBossHealth / (mBossBaseHealth / 5)));

	if (!mHUDUnits.empty())
	{
		mHUDUnits.at(0)->setAnimationByIndex(phase % 2 == 0 || mBossHealth <= 0 ? 0 : 1);

	}

	string key = std::to_string(mCurrentLanguage) + "phase" + std::to_string(phase);
	bossText = mpDataReader->findStringDataByKey(key);
}

void HUD::update(float deltaTime, float fps)
{
	mFPS = fps;

	if (!mPause && mStartGame)
	{
		//is time supposed to be paused when the game is paused?
		mTimeElapsed += deltaTime;
	}
	if (mScore <= 0 && !mGameOver)
	{
		GameOverEvent gameOver;
		EventSystem::getInstance()->fireEvent(gameOver);
	}
}


void HUD::createPauseMenu()
{
	//std::cout << "CALLED" << std::endl;
	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(200, 200), *mpFontSmall, *mpColor, mpDataReader->findStringDataByKey(std::to_string(mCurrentLanguage) + "Pause"));
	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(200, 300), *mpFontSmall, *mpColor, mpDataReader->findStringDataByKey(std::to_string(mCurrentLanguage) + "Esc"));
	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(200, 400), *mpFontSmall, *mpColor, mpDataReader->findStringDataByKey(std::to_string(mCurrentLanguage) + "Space"));
}

void HUD::createGameMenu()
{
	
	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(0, 0), *mpFont, *mpColor, mpDataReader->findStringDataByKey(std::to_string(mCurrentLanguage) + "FPS") + std::to_string(1000 / mFPS));
	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(0, 100), *mpFont, *mpColor, mpDataReader->findStringDataByKey(std::to_string(mCurrentLanguage) + "Health") + std::to_string((int)mPlayerHealth));
	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(100, 500), *mpFont, *mpColor, bossText);

	//  + std::to_string(mScore)
	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(450, 0), *mpFont, *mpColor, mpDataReader->findStringDataByKey(std::to_string(mCurrentLanguage) + "Time") + std::to_string(static_cast<int>(mTimeElapsed * 0.001)));
	if(!mPause && mStartGame == true)
	{
		mpBufferManager->getBuffer("HUD")->writeText(Vector2D(800, 500), *mpFont, *mpColor, mpDataReader->findStringDataByKey(std::to_string(mCurrentLanguage) + "EscP"));
	}
	
	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(600, 100), *mpFont, *mpColor, std::to_string((int)(mBossHealth * 10)));


	for (unsigned int i = 0; i < mHUDUnits.size(); i++)
	{
		Unit* pTarget = mHUDUnits.at(i);
		GraphicsSystem::getBackBuffer()->draw(pTarget->getLoc(), pTarget->getSprite(), pTarget->getSize());
		//mpBufferManager->getBuffer("HUD")->draw(pTarget->getLoc(), pTarget->getSprite(), pTarget->getSize());
	}
}


void HUD::createStartScreen()
{
	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(200, 300), *mpFontSmall, *mpColor, mpDataReader->findStringDataByKey(std::to_string(mCurrentLanguage) + "Start"));
}

void HUD::createGameOverScreen()
{
	clearHUD();
	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(200, 200), *mpFontSmall, *mpColor, mpDataReader->findStringDataByKey(std::to_string(mCurrentLanguage) + "Over"));
	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(200, 300), *mpFontSmall, *mpColor, mpDataReader->findStringDataByKey(std::to_string(mCurrentLanguage) + "Thanks"));
	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(200, 400), *mpFontSmall, *mpColor, mpDataReader->findStringDataByKey(std::to_string(mCurrentLanguage) + "Again"));

	mpBufferManager->getBuffer("HUD")->writeText(Vector2D(100, 500), *mpFont, *mpColor, bossText);
}

void HUD::addUnitToHUD(Unit* pUnit)
{
	mHUDUnits.push_back(pUnit);
}

void HUD::clearHUD()
{
	mpBufferManager->getBuffer("HUD")->setToColor(Color(0.0f, 0.0f, 0.0f, 0.0f));
	mFPS = 0;
	mTimeElapsed = 0;
	mScore = mDefualtScore;

	//after deleteing hud units in the unit create THIS NEEDS TO BE CLEANED OUT
	mHUDUnits.clear();
}

void HUD::draw()
{
	mpBufferManager->getBuffer("HUD")->setToColor(Color(0.0f, 0.0f, 0.0f, 0.0f));

	if (!mGameOver)
	{
		if (!mStartGame)
		{
			createStartScreen();
		}
		else
		{
			if (mPause)
			{
				createPauseMenu();
			}
			
		}

		createGameMenu();
	}
	else
	{
		createGameOverScreen();
	}
	GraphicsSystem::getBackBuffer()->draw(Vector2D(0, 0), *mpBufferManager->getBuffer("HUD"), 1.0f);
	

}
