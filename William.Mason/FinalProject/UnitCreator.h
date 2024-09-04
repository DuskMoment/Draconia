#pragma once

#include <Trackable.h>
#include <Vector2D.h>
#include <GraphicsSystem.h>
#include <vector>
#include <EventListener.h>
#include <Vector2D.h>

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

class Player;
class Boss;

class UnitCreator : public EventListener
{
public:
	void init();
	void cleanup();
	void handleEvent(const Event& theEvent);

	static void createInstance(GraphicsBufferManager* pGBM, UnitManager* pUM, DataReader* pDR);
	static UnitCreator* getInstance();
	static void deleteInstance();

	void loadAnim(std::string bufferKey, std::string assetPath, int spritesDown,
		int spritesAcross, int offsetX, int offsetY, int pixelWidth, int pixelHeight, std::vector<Sprite>& vec, Animation*& anim, 
		int frames = FRAMES_15, int widthOffset = 0, int heightOffset = 0, int hitboxOffsetX = 0, int hitboxOffsetY = 0);

	void createStartingEntities();
	void createHUDUnits();

	Player* createPlayer(Vector2D loc, Vector2D vel, int speed);
	Boss* createBoss(Vector2D loc, Vector2D vel, int speed);
	
	void createPlayerFireball(float size, Vector2D loc = Vector2D(0, 0));

	void createRandomBossFireball();
	void createBossPatternA();
	void createBossPatternB();
	void createBossPatternC();
	void createBossFireBall(Vector2D loc, Vector2D vel, int speed);
	void createTailwind();
	void createTailwind(Vector2D loc, Vector2D vel, int speed);

	int getDiff() { return mpDifficulty; };

	Player* mpPlayer;
private:
	UnitCreator(GraphicsBufferManager* pGBM, UnitManager* pUM, DataReader* pDR);
	~UnitCreator();

	UnitManager* mpUnitManager; 
	GraphicsBufferManager* mpGraphicsBufferManager;
	DataReader* mpDataReader;

	Boss* mpBoss;
	Unit* mpChat;
	// we don't own these, this is just a pointer to each object in game
	// so not members

	int mpDifficulty = 1;

	static UnitCreator* mpInstance;

	enum FrameSpeeds
	{
		FRAMES_30 = 30,
		FRAMES_15 = 15,
		FRAMES_5 = 5,
	};

	/* VALUES FOR DATA MANAGER */
	int BOSS_BULLET_SPEED_SLOW = 100;
	int BOSS_BULLET_SPEED_MEDIUM = 200;
	int BOSS_BULLET_SPEED_FAST = 300;

	int mBossPatternAXStart = 700;
	int mBossPatternAXEnd = 900;
	int	mBossPatternAXDiff = 100;
	int mBossPatternAXStep = 5;
	int	mBossPatternAYStart = 500;
	int	mBossPatternAYEnd = 0;
	int	mBossPatternAYDiff = 25;
	int	mBossPatternAYGap = 300;
	int mBossPatternATailwindX = 800;
	int mBossPatternATailwindY = 550;

	int mBossPatternBXStart = 700;
	int mBossPatternBXEnd = 2500;
	int mBossPatternBXDiff = 50;
	int mBossPatternBYStart = 000;
	int mBossPatternBYEnd = 600;
	int mBossPatternBYDiff = 100;
	int mBossPatternBTicks = 300;

	int	mBossPatternCXStart = 700;
	int	mBossPatternCXEnd = 900;
	int	mBossPatternCXDiff = 50;
	int	mBossPatternCYStart = 0;
	int	mBossPatternCYEnd = 800;
	int	mBossPatternCYDiff = 100;
	int	mBossPatternCLineDiff = 20;
	int	mBossPatternCLineLengths = 200;
	int	mBossPatternCLineSkip = 180;
	int	mBossPatternCLineGap = 60;
	int mBossPatternCLineX = 1400;

	int mBossRandomYMin = 100;
	int mBossRandomYRange = 500;
	int mBossRandomX = 1000;

	/* ANIMATION VALUES */

	std::vector<Animation> mBenemothAnimsVec;
	std::vector<Animation> mAnimationsVec;
	std::vector<Animation> mBossFireballVec;
	std::vector<Animation> mDragonAnimsVec;
	std::vector<Animation> mTailwindAnimsVec;
	std::vector<Animation> mChatAnimsVec;
	//animations and sprites

	Animation* mpRedBallAnimation;
	Animation* mpBlueBallAnimation;

	Animation* mpDragonAnimation;

	Animation* mpFireballAnimation;
	Animation* mpBossFireballAnimation;

	Animation* mpBehemothFlyAnimation;

	Animation* mpTailwindAnimation;

	Animation* mpDragonChat;
	Animation* mpBehemothChat;

	std::vector<Sprite> mRedBallSpriteVec;
	std::vector<Sprite> mBlueBallSpriteVec;
	std::vector<Sprite> mDragonSpriteVec;
	std::vector<Sprite> mFireballSpriteVec;
	std::vector<Sprite> mBossFireballSpriteVec;
	std::vector<Sprite> mBehemothFlyVec;
	std::vector<Sprite> mTailwindVec;
	std::vector<Sprite> mDragonChatVec;
	std::vector <Sprite> mBehemothChatVec;

	const std::string M_STEPS_FILENAME = "woods.png";

	const std::string M_FILE_TYPE = ".png";
	const std::string M_FEMALE_PERSON = "character_femalePerson_walk";
	const std::string M_KENNEY_ASSET_PATH = "kenney_toon-characters\\Female person\\PNG\\Poses\\";
	const std::string M_SMURF_FILENAME = "smurf_sprites.png";
	const std::string M_ASSET_PATH = "..\\..\\shared\\assets\\";

	const std::string M_MYASSETS_PATH = "..\\..\\William.Mason\\assets\\";
	const std::string M_DRAGON_PATH = "sprites\\reddragon.png";
	const std::string M_DRAGON_TALK_PATH = "sprites\\dragonchat.png";
	const std::string M_BEHEMOTH_TALK_PATH = "sprites\\mechdragonchat.png";
	const std::string M_FIREBALL_PATH = "sprites\\fireball.png";
	const std::string M_BOSS_FIREBALL_PATH = "sprites\\evilfireball.png";
	const std::string M_BEHEMOTH_PATH = "sprites\\mechdragon.png";
	const std::string M_TAILWIND_PATH = "sprites\\tailwind.png";

	//temp
	const std::string M_SOUND_FILE = "FANFARE.WAV";
	const std::string M_MINDTRAP_PATH = "minetrap\\";

	const unsigned int M_PIXEL_WIDTH = 32;
	const unsigned int M_PIXEL_HEIGHT = 32;
	const unsigned int M_SPRITES_ACROSS = 5;
	const unsigned int M_SPRITES_DOWN = 2;
	const unsigned int M_FILES_IN_FOLDER = 8;
	const unsigned int M_RED_SPRITE_OFFSET_X = 0;
	const unsigned int M_RED_SPRITE_OFFSET_Y = 4;
	const unsigned int M_BLUE_SPRITE_OFFSET_X = 6;
	const unsigned int M_BLUE_SPRITE_OFFSET_Y = 4;
};