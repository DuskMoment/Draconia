#pragma once
#include <Trackable.h>
#include <GraphicsBufferManager.h>
#include <Eventlistener.h>
#include <vector>

class GraphicsBufferManager;
class DataReader;
class Font;
class Color;
class Unit;

class HUD : public EventListener
{
public:
	HUD(GraphicsBufferManager* bufferManager, const DataReader* dataReader);
	~HUD();
	
	//creates the first buffer with all the stuff on it
	void init(int width,int hight);
	void cleanup();
	void handleEvent(const Event& theEvent);

	void update(float deltaTime, float fps);

	void createPauseMenu();
	void createGameMenu();
	void createStartScreen();
	void createGameOverScreen();

	void setPause(bool condition) { mPause = condition; };
	void setStartGame(bool condition) { mStartGame = condition; };
	void setGameOver(bool condition) { mGameOver = condition; };

	int getTime() { return mTimeElapsed; };
	void setTime(int time) { mTimeElapsed = time; };

	void addUnitToHUD(Unit* pUnit);

	void clearHUD();

	void updateChat();

	void draw();

private:
    GraphicsBufferManager* mpBufferManager;
	const DataReader* mpDataReader;

	float mFPS;
	int mTimeElapsed = 0;
	int mScore;
	int mDefualtScore;
	bool mPause;
	bool mStartGame = false;
	bool mGameOver = false;

	// datamanager should catch the initial version of this number
	float mBossHealth = 50;
	float mBossBaseHealth = 50;
	float mPlayerHealth;

	int mPosPoints;
	int mNegPoints;

	std::vector<Unit*> mHUDUnits;

	std::string bossText;

	int mCurrentLanguage = 0;

	//temp
	const std::string ASSET_PATH = "..\\..\\shared\\assets\\";
	const std::string FONT_FILENAME = "cour.ttf";
	const int FONT_SIZE = 48;
	const int FONT_SIZE_SMALL = 32;

	Font* mpFont;
	Font* mpFontSmall;

	Color* mpColor;

};

