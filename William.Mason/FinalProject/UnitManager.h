#pragma once
#include <Trackable.h>
#include <vector>
#include <string>
#include <MemoryPool.h>

class GraphicsBufferManager;
class Animation;
class Vector2D;
class Unit;
class DataReader;

class UnitManager : public Trackable
{
	friend Unit;
public:
	UnitManager(int poolSize);
	~UnitManager();

	void cleanup();
	bool init(const DataReader* dataReader, int poolSize);

	void addUnit(Unit* unit);
	void createUnit(std::vector<Animation> animation, Vector2D loc, int highVel, int lowVel, int highSpeed, int lowSpeed);
	void createFireball(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, float size);

	void destroyUnit(Unit* pUnit);
	void destroyUnitAtLocation(Vector2D loc);
	void changeAnimationAtLocation(Vector2D loc);
	void changeSpeedMod(int mod) { mSpeedMod = mod; };
	void increaseSpeed(float deltaTime);

	void draw();
	void checkCollisions(Unit* pUnit);
	Unit* getUnit();
	std::vector<Unit*> getUnitVector() { return mpUnitVec; };
	
	void animate(bool shouldAnimate);

	void update(float deltaTime);

	bool getShouldAnimate() { return mShouldAnimate; };

	int getSpawnChance() { return mSpawnChance; }
	void increaseSpawnChance(int ammount) { mSpawnChance += ammount; }

private:
	std::vector<Unit*> mpUnitVec;

	// when you want to destroy a unit, add it to this vector instead of hard destroying it
	// is what i'm going for, since then we can clean up the units at the end of update
	// and not risk altering that collection while doing everything else
	std::vector<Unit*> mpUnitsToDestroyVec;

	int mDefaultSpawnChance;
	int mSpawnChance;

	float mSpeedIncreseTimer = 0;
	int mSpeedMod;
	int mSpeedIncreaseAmmount;
	int mTimeTillIncrease;
	bool mShouldAnimate = true;

	const DataReader* mpDataReader;
	
	MemoryPool mPool;
};

