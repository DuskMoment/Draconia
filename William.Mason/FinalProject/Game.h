#pragma once

#include <Trackable.h>
#include <Vector2D.h>
#include <GraphicsSystem.h>
#include <vector>
#include <EventListener.h>

class HUD;
class GraphicsSystem;
class InputSystem;
class Unit;
class Animation;
class GraphicsBufferManager;
class UnitManager;
class InputTranslator;
class SoundManager;
class DataReader;
class UnitCreator;
class Menue;

class Player;
class Boss;

class Game : public EventListener
{

public:
	static void createInstance();
	static Game* getInstance();
	static void deleteInstance();

	bool init(int width, int height);
	void cleanup();
	void pollInput();
	void render();
	void resetGame(bool loadFromSave);
	void update(float deltaTime);
	void doLoop(); // doLoop – contains the actual loop ( I suggest a while loop). Things to do, not necessarily in this
					//order:
					//o Get user input
					//o Adjust game state(based on user input and other automatic factors)
					//o Draw current game state
					//o Wait until the target amount of time has elapsed
					//do timming here too
	void startNewGame();
	void handleEvent(const Event& theEvent);

	void renderUnitInHUD(Unit* pUnit); // this is not a very good place for this

	//void setupAnimation(
	//	int spritesDown, int spritesAcross, 
	//	int width, int height, 
	//	std::string bufferName, vector<Sprite> spriteVec, Animation* pAnimation, 
	//	int offsetX = 0, int offsetY = 0, int frames = FRAMES_15, bool looping = true);

	void saveGame();
	void loadGame();

private:

	//make it "static"
	Game();
	~Game();

	static Game* mpInstance;

	enum FrameSpeeds
	{
		FRAMES_30 = 30,
		FRAMES_15 = 15,
		FRAMES_5 = 5,
	};

	InputSystem* mpInputSystem;
	GraphicsSystem* mpGraphicsSystem;
	UnitManager* mpUnitManager;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SoundManager* mpSoundMangager; 
	UnitCreator* mpUnitCreator;

	Player* mpPlayer;
	Boss* mpBoss;
	
	float mFPS = 0;

	//listeners
	InputTranslator* mpInputTranslatorListener = nullptr;

	//bools
	bool mGameQuit = false;
	bool mPauseGame = true;
	bool mGameOver = false;
	bool mGameStart = false;

	//dataReader
	DataReader* mpDataReader;
	
	//timers
	float mSpeedIncresseTimer = 0;

	//consts
	 unsigned int mWidth = 0;
	 unsigned int mHeight = 0;

	//temp
	const std::string M_SOUND_FILE = "FANFARE.WAV";
	const std::string M_MINDTRAP_PATH = "minetrap\\";
	const std::string M_SOUND_PATH = "..\\..\\William.Mason\\assets\\sounds\\";
	HUD* mpHUD;
	Menue* mpMenue;

	const float M_ELASPED_TIME = 20;

	const Color DEFAULT_COLOR = Color(0.0f, 0.0f, 0.0f);

	Vector2D mInputDirection;

	bool mGameScene = false;
};

//extern Game* gpGame; //extern tell the compliler has this function signeture but for a var
