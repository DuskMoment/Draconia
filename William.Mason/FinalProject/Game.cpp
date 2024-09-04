#pragma once

#include<string>
#include "Game.h"
#include "Unit.h"
#include "UnitManager.h"
#include <InputSystem.h>
#include <GraphicsSystem.h>
#include <GraphicsBuffer.h>
#include <Sprite.h>
#include <Animation.h>
#include <PerformanceTracker.h>
#include <GraphicsBufferManager.h>
#include <EventSystem.h>
#include "SoundManager.h"
#include "InputTranslator.h"
#include "HUD.h"
#include "Menue.h"
#include "UnitCreator.h"

//entites
#include "Player.h"
#include "Boss.h"
#include "PlayerFireball.h"
#include "BossFireball.h"
#include "Tailwind.h"


//data reader
#include "DataReader.h"
#include <fstream>


//events

#include "QuitGame.h"
#include "PauseAllAnimations.h"
#include "UnitChangeEvent.h"
#include "PlaySoundEvent.h"
#include "PauseGameEvent.h"
#include "PlayerDirectionEvent.h"
#include "BossHealthEvent.h"
#include "DiffucltyChangeEvent.h"
#include "PlayerHealthEvent.h"


//Game* gpGame = nullptr; // now will only make one Game gGame;

Game* Game::mpInstance = nullptr;

void Game::startNewGame()
{
}

void Game::handleEvent(const Event& theEvent)
{
	std::cout << "game event recieved" << endl;

	if (theEvent.getType() == QUIT_GAME_EVENT)
	{
		std::cout << "quit game event recieved" << endl;
		if (mPauseGame)
		{
			mGameQuit = true;
			saveGame();
		}
		else
		{
			mPauseGame = true;

			mpHUD->setPause(mPauseGame);
			mpHUD->setStartGame(mGameStart);
		}
	}

	else if (theEvent.getType() == CHANGE_ANIMATION_EVENT)
	{
		if (mpUnitManager->getUnit() != nullptr)
		{
			int currentIndex = mpUnitManager->getUnit()->getAnimationIndex();
			if (currentIndex == 0)
			{
				mpUnitManager->getUnit()->setAnimationByIndex(1);
			}
			else
			{
				mpUnitManager->getUnit()->setAnimationByIndex(0);
			}
		}

	}
	else if (theEvent.getType() == PAUSE_ANIMATION_EVENT)
	{
		if (mpUnitManager->getShouldAnimate())
		{
			mpUnitManager->animate(false);
		}
		else if(!mpUnitManager->getShouldAnimate())
		{
			mpUnitManager->animate(true);

		}

	}
	else if (theEvent.getType() == UNIT_CHANGE_EVENT)
	{
		const UnitChangeEvent& changeEvent = static_cast<const UnitChangeEvent&>(theEvent);

		if (!changeEvent.getShouldDelete())
		{
			mpUnitManager->changeAnimationAtLocation(changeEvent.getLoc());
		}
	}
	else if (theEvent.getType() == PAUSE_GAME_EVENT)
	{
		const PauseGameEvent& pauseGameEvent = static_cast<const PauseGameEvent&>(theEvent);

		if (!mGameOver)
		{
			if (mGameStart == false && !pauseGameEvent.getShouldQuit())
			{
				mGameStart = true;
			}

			if (mPauseGame == false && mGameStart && pauseGameEvent.getShouldQuit() || mGameStart == false)
			{
				mPauseGame = true;
			}
			else if (pauseGameEvent.getShouldQuit() && mGameStart)
			{
				QuitGame quit;

				EventSystem::getInstance()->fireEvent(quit);
			}
			else
			{
				mPauseGame = false;
			}

			mpHUD->setPause(mPauseGame);
			mpHUD->setStartGame(mGameStart);
		}
		
	}
	else if (theEvent.getType() == GAME_OVER_EVENT)
	{
		mGameOver = true;
		mpHUD->setGameOver(mGameOver);
		mPauseGame = true;
		mpHUD->setPause(mPauseGame);
	}
	else if (theEvent.getType() == RESTART_GAME_EVENT)
	{
		if (mGameOver)
		{
			resetGame(false);
		}
		
	}
	else if (theEvent.getType() == PLAYER_DIRECTION_EVENT)
	{
		const PlayerDirectionEvent& playerDirectionEvent = static_cast<const PlayerDirectionEvent&>(theEvent);

		Vector2D val = Vector2D(0, 0);

		mpUnitCreator->mpPlayer->setInput(playerDirectionEvent.getDir(), playerDirectionEvent.getGo());

		switch (playerDirectionEvent.getDir())
		{
		case Up:
			val.setY(playerDirectionEvent.getGo() ? -100 : 0);
			break;
		case Down:
			val.setY(playerDirectionEvent.getGo() ? 100 : 0);
			break;
		case Left:
			val.setX(playerDirectionEvent.getGo() ? -100 : 0);
			break;
		case Right:
			val.setX(playerDirectionEvent.getGo() ? 100 : 0);
			break;
		}

		//mpPlayer->setVelocity(val);
		
	}
	

}

void Game::saveGame()
{
	//just dont want to have to re type it over and over again
	using namespace std;

	ofstream theStream;
	theStream.open("SaveGame.txt");
	theStream.clear();

	std::vector<Unit*> pUnits = mpUnitManager->getUnitVector();

	//data location, animation index, boss health, time? 
	for (unsigned int i = 0; i < pUnits.size(); i++)
	{
		Vector2D loc = pUnits.at(i)->getLoc();
		Vector2D vel = pUnits.at(i)->getVel();

		int animationIndex = pUnits.at(i)->getAnimationIndex();
		int myTeam = pUnits.at(i)->getMyTeam();

		Boss* pBoss = dynamic_cast<Boss*>(pUnits.at(i));
		//save the boss health, time before last pattern
		if (pBoss != NULL)
		{
			float bossHealth = pBoss->getBossHealth();
			float timeSinceLastPattern = pBoss->getTimeSinceLastPattern();

			cout << "Boss Saved!" << endl;
			theStream << "BOSS" << endl;
			theStream << bossHealth << endl;
			theStream << timeSinceLastPattern << endl;
			
		}

		BossFireball* pBossFireBall = dynamic_cast<BossFireball*>(pUnits.at(i));
		if (pBossFireBall != NULL)
		{
			int speed = pBossFireBall->getSpeed();
			//tell the file that any info put here is for the bossFireBall
			std::cout << "BossFireBallSaved!" << std::endl;
			theStream << "BOSS_FIRE_BALL" << endl;
			theStream << speed << endl;
		}

		Player* pPlayer = dynamic_cast<Player*>(pUnits.at(i));
		if (pPlayer != NULL)
		{
			//tell the file that player data starts here
			int health = pPlayer->getPlayerHealth();
			std::cout << "PlayerSaved!" << std::endl;

			theStream << "PLAYER" << endl;
			theStream << health << endl;
		}

		PlayerFireball* pPlayerFireBall = dynamic_cast<PlayerFireball*>(pUnits.at(i));
		if (pPlayerFireBall != NULL)
		{
			//tell the file that playerFireBall Data starts here
			std::cout << "PlayerFireBallSaved!" << std::endl;
			theStream << "PLAYER_FIRE_BALL" << endl;
			float size = pPlayerFireBall->getSize();
			theStream << size << endl;
		}

		Tailwind* pTailWind = dynamic_cast<Tailwind*>(pUnits.at(i));
		if (pTailWind != NULL)
		{
			std::cout << "TailWind Saved!" << std::endl;

			theStream << "TAIL_WIND" << endl;
			float speed = pTailWind->getSpeed();
			theStream << speed << endl;

		}

		//shared stats
		theStream << loc.getX()<< endl;
		theStream << loc.getY() << endl;
		theStream << vel.getX() << endl;
		theStream << vel.getY() << endl;
		theStream << animationIndex << endl;
		theStream << myTeam << endl;
	}

	theStream << "MISC" << endl;
	theStream << mpHUD->getTime() << endl;
	theStream << mpSoundMangager->getMute() << endl;
	theStream << "GAME" << endl;
	theStream << mpUnitCreator->getDiff() << endl;

	theStream.close();
	
}

void Game::loadGame()
{
	using namespace std;

	ifstream theStream;
	theStream.open("SaveGame.txt");

	mpUnitCreator->createHUDUnits();

	while (theStream)
	{
		string data;
		theStream >> data;

		if (data == "PLAYER")
		{
			int health;
			Vector2D loc;
			Vector2D vel;
			int aniIndex;
			int myTeam;

			//health
			theStream >> health;

			//loc
			string stringToInt;
			theStream >> stringToInt;
			loc.setX(stoi(stringToInt));
			theStream >> stringToInt;
			loc.setY(stoi(stringToInt));

			//vel
			theStream >> stringToInt;
			vel.setX(stoi(stringToInt));
			theStream >> stringToInt;
			vel.setY(stoi(stringToInt));

			//aniIndex
			theStream >> aniIndex;

			//team
			theStream >> myTeam;
			Player* pPlayer = mpUnitCreator->createPlayer(loc, vel, 0);

			pPlayer->setAnimationByIndex(aniIndex);
			pPlayer->setPlayerHealth(health);
			pPlayer->setMyTeam(myTeam);

			PlayerHealthEvent event(health);
			EventSystem::getInstance()->fireEvent(event);
		}
		else if (data == "BOSS")
		{
			//specific
			float health;
			float timeSinceLastAttack;

			//universal
			Vector2D loc;
			Vector2D vel;
			int aniIndex;
			int myTeam;

			//health
			theStream >> health;
			theStream >> timeSinceLastAttack;

			//loc
			string stringToInt;
			theStream >> stringToInt;
			loc.setX(stoi(stringToInt));
			theStream >> stringToInt;
			loc.setY(stoi(stringToInt));

			//vel
			theStream >> stringToInt;
			vel.setX(stoi(stringToInt));
			theStream >> stringToInt;
			vel.setY(stoi(stringToInt));

			//aniIndex
			theStream >> aniIndex;

			//team
			theStream >> myTeam;

			Boss* pBoss = mpUnitCreator->createBoss(loc, vel, 0);

			pBoss->setBossHealth(health);
			BossHealthEvent healthEvent(health);

			EventSystem::getInstance()->fireEvent(healthEvent);

			pBoss->setTimeSinceLastPattern(timeSinceLastAttack);
			pBoss->setAnimationByIndex(aniIndex);
			pBoss->setMyTeam(myTeam);
		}
		else if (data == "BOSS_FIRE_BALL")
		{
			Vector2D loc;
			Vector2D vel;
			int aniIndex;
			int myTeam;
			int speed;

			theStream >> speed;
			//loc
			string stringToInt;
			theStream >> stringToInt;
			loc.setX(stoi(stringToInt));
			theStream >> stringToInt;
			loc.setY(stoi(stringToInt));

			//vel
			theStream >> stringToInt;
			vel.setX(stoi(stringToInt));
			theStream >> stringToInt;
			vel.setY(stoi(stringToInt));

			//aniIndex
			theStream >> aniIndex;

			//team
			theStream >> myTeam;
			mpUnitCreator->createBossFireBall(loc, vel, speed);

		}
		else if (data == "PLAYER_FIRE_BALL")
		{
			Vector2D loc;
			Vector2D vel;
			int aniIndex;
			int myTeam;
			float size;

			theStream >> size;
			//loc
			string stringToInt;
			theStream >> stringToInt;
			loc.setX(stoi(stringToInt));
			theStream >> stringToInt;
			loc.setY(stoi(stringToInt));

			//vel
			theStream >> stringToInt;
			vel.setX(stoi(stringToInt));
			theStream >> stringToInt;
			vel.setY(stoi(stringToInt));

			//aniIndex
			theStream >> aniIndex;

			//team
			theStream >> myTeam;

			mpUnitCreator->createPlayerFireball(size, loc);
		}
		else if (data == "TAIL_WIND")
		{
			Vector2D loc;
			Vector2D vel;
			int aniIndex;
			int myTeam;
			int speed;

			theStream >> speed;
			//loc
			string stringToInt;
			theStream >> stringToInt;
			loc.setX(stoi(stringToInt));
			theStream >> stringToInt;
			loc.setY(stoi(stringToInt));

			//vel
			theStream >> stringToInt;
			vel.setX(stoi(stringToInt));
			theStream >> stringToInt;
			vel.setY(stoi(stringToInt));

			//aniIndex
			theStream >> aniIndex;

			//team
			theStream >> myTeam;

			mpUnitCreator->createTailwind(loc,vel,speed);
			
		}
		else if (data == "MISC")
		{
			//time
			int time;
			bool mute;
		
			theStream >> time;
			theStream >> mute;
			
			mpHUD->setTime(time);
			mpSoundMangager->setMute(mute);
			
		}
		else if (data == "GAME")
		{
			int diff;
			theStream >> diff;

			cout << "DIFF " << diff << endl;

			DiffucltyChangeEvent event(diff);
			EventSystem::getInstance()->fireEvent(event);

		}

	}

	
	theStream.close();

}

Game::Game()
{	
	mpInputSystem = nullptr;
	mpGraphicsSystem = nullptr;
	mpUnitManager = nullptr;
	mpGraphicsBufferManager = nullptr;
	mpSoundMangager = nullptr;
	mpDataReader = nullptr;
	mpHUD = nullptr;
	mpBoss = nullptr;
	mpMenue = nullptr;
	mpPlayer = nullptr;
	mpUnitCreator = nullptr;
	
}

Game::~Game()
{
	cleanup();	
}

void Game::createInstance()
{
	if (mpInstance == nullptr)
	{
		mpInstance = new Game;
	}
}

Game* Game::getInstance()
{
	return mpInstance;
}

void Game::deleteInstance()
{
	if (mpInstance != nullptr)
	{
		delete mpInstance;
	}
	mpInstance = nullptr;
}

bool Game::init(int width, int height)
{
	mWidth = width;
	mHeight = height;
	mpGraphicsSystem = new GraphicsSystem;

	if (!mpGraphicsSystem->init(mWidth, mHeight))
	{
		std::cout << "Graphics system init failed" << std::endl;
		return false;
	}
	mpInputSystem = new InputSystem;
	if (!mpInputSystem->init(*mpGraphicsSystem->getWindow()))
	{
		std::cout << "InputSystem init failed" << std::endl;
		return false;
	}
	//INIT OF EVENT SYSTEM
	
	
	//data reader
	mpDataReader = new DataReader("data.txt");
	mpDataReader->readFile();

	//listeners
	mpInputTranslatorListener = new InputTranslator;

	//event subscriptions
	EventSystem::getInstance()->addListener((EventType)QUIT_GAME_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)CHANGE_ANIMATION_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PAUSE_ANIMATION_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)UNIT_CHANGE_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAY_SOUND_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PAUSE_GAME_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)GAME_OVER_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)RESTART_GAME_EVENT, this);
	EventSystem::getInstance()->addListener((EventType)PLAYER_DIRECTION_EVENT, this);
	
	// pool size should be data driven 
	mpUnitManager = new UnitManager(200);
	mpUnitManager->init(mpDataReader, 200);

	mpGraphicsBufferManager = new GraphicsBufferManager;
	mpSoundMangager = new SoundManager;

	mpSoundMangager->init(20);

	mpSoundMangager->addSound("PointCollected", mpDataReader->findStringDataByKey("PointCollected"));
	mpSoundMangager->addSound("PointLost", mpDataReader->findStringDataByKey("PointLost"));
	mpSoundMangager->addSound("gameOver", mpDataReader->findStringDataByKey("gameOver"));
	mpSoundMangager->addSound("fireballSmall", M_SOUND_PATH + "Spell_Uni_FireCast_02.wav");
	mpSoundMangager->addSound("fireballLarge", M_SOUND_PATH + "FX_ExplosionProjectileLaunchMedium_09.ogg");
	mpSoundMangager->addSound("charge", M_SOUND_PATH + "PreCastFireLow.wav");
	mpSoundMangager->addSound("tailwind", M_SOUND_PATH + "Spell_SH_Windfury_Impact02.wav");
	mpSoundMangager->addSound("playerDamage", M_SOUND_PATH + "FX_ExplosionProjectileLaunchSmall_01.ogg");
	mpSoundMangager->addSound("bossDamageLow", M_SOUND_PATH + "LavaDamageC.ogg");
	mpSoundMangager->addSound("bossDamageHigh", M_SOUND_PATH + "SPELL_MA_REVAMP_Fireball_Impact_01.ogg");
	mpSoundMangager->addSound("music", M_SOUND_PATH + "DRUMMY_THING_WIP_4.mp3", true);

	EventSystem::getInstance()->fireEvent(PlaySoundEvent("music"));
	

	UnitCreator::createInstance(mpGraphicsBufferManager, mpUnitManager, mpDataReader);
	mpUnitCreator = UnitCreator::getInstance();

	mpGraphicsBufferManager->createBuffer("gameBuffer",width, height, DEFAULT_COLOR);

	//no default float vector consturctor :( this also sets it to the middle of the screen. 
	Vector2D loc(0, 0);
	loc.setX(mWidth/2);
	loc.setY(mHeight/2);

	//temp
	mpHUD = new HUD(mpGraphicsBufferManager, mpDataReader);
	mpHUD->init(width, height);

	mpUnitCreator->createStartingEntities();

	mpMenue = new Menue(mpGraphicsBufferManager, mpDataReader);
	mpMenue->init(width, height);

	//loadGame();

	mpSoundMangager->setMusicVolume(10);

	return true;
}


void Game::cleanup()
{
	delete mpMenue;
	mpMenue = nullptr;

	UnitCreator::deleteInstance();
	mpUnitCreator = nullptr;

	delete mpDataReader;
	mpDataReader = nullptr;

	//listeners 
	delete mpInputTranslatorListener;
	mpInputTranslatorListener = nullptr;
	
	//hud
	delete mpHUD;
	mpHUD = nullptr;

	//systems
	delete mpSoundMangager;
	mpSoundMangager = nullptr;
	delete mpGraphicsBufferManager;
	mpGraphicsBufferManager = nullptr;
	delete mpUnitManager;
	mpUnitManager = nullptr;
	delete mpGraphicsSystem;
	mpGraphicsSystem = nullptr;
	delete mpInputSystem;
	mpInputSystem = nullptr;

	//delete mpPlayer;
	//mpPlayer = nullptr;
	
	//delete mpBoss;
	//mpBoss = nullptr;
}



void Game::render()
{
	
	//then draw
	GraphicsSystem::getBackBuffer()->setToColor(Color(0.0f,0.0f,0.0f,0.0f));
	GraphicsBuffer* pTarget = mpGraphicsBufferManager->getBuffer("gameBuffer");
	GraphicsSystem::getBackBuffer()->draw(ZERO_VECTOR2D,*pTarget, 1.0);


	
	if (!mpMenue->getIsActive())
	{
		mpHUD->draw();
		mpUnitManager->draw();
	}
	else
	{
		mpMenue->draw();
	}
	

	//mpPlayer->draw();
	//mpBoss->draw();

	//after drawing flip
	mpGraphicsSystem->flip();
}

void Game::resetGame(bool loadFromSave)
{
	mpGraphicsBufferManager->getBuffer("gameBuffer")->setToColor(DEFAULT_COLOR);

	mpUnitCreator->cleanup();

	mpUnitManager->cleanup();
	mpUnitManager->changeSpeedMod(0);

	mpHUD->clearHUD();

	mpUnitCreator->init();

	if (!loadFromSave)
	{
		mpUnitCreator->createStartingEntities();
	}

	mPauseGame = true;
	mpHUD->setPause(mPauseGame);


	mGameOver = false;
	mpHUD->setGameOver(mGameOver);
	mGameStart = false;
	mpHUD->setStartGame(mGameStart);

	

}

void Game::update(float deltaTime)
{
	mpHUD->update(M_ELASPED_TIME, mFPS);

	if (!mPauseGame)
	{
		mpUnitManager->update(deltaTime);
	}
}
	

void Game::doLoop()
{
	PerformanceTracker tracker;
	Timer theTime;

	while (!mGameQuit)
	{
		//performance tracker
		tracker.clearTracker("loop");
		tracker.startTracking("loop");

		//timer && zeros it out
		theTime.start();

		//poll input
		//pollInput();
		mpInputSystem->update();
		
		//has a chance to spawn a unit every frame
		//spawnUnit();

		update(M_ELASPED_TIME);
		//start of draw updates
		render();

		theTime.sleepUntilElapsed(M_ELASPED_TIME);
		tracker.stopTracking("loop");
		mFPS = tracker.getElapsedTime("loop");
		//std::cout << "loop deanLib tracker: " << tracker.getElapsedTime("loop") << std::endl;
		
	}
}

void Game::renderUnitInHUD(Unit* pUnit)
{
	pUnit->mRenderInHUD = true;
	mpHUD->addUnitToHUD(pUnit);
}

