#pragma once
#include <Trackable.h>
#include <Vector2D.h>
#include <vector>
#include <utility>
#include "PlayerDirectionEvent.h"
#include "Unit.h"

class Sprite;
class Animation;
class GraphicsBuffer;
class GraphicsSystem;
class UnitManager;
class EventSystem;
class DataReader;

// i want this class to inherit from unit :)
class Boss : public Unit
{
	friend UnitManager;
public:
	void update(float deltaTime);//should be 16.7;
	//void addAnimation(const Animation& newAnimaiton);
	//void setPosition(const Vector2D& newLoc);

	//void draw();
	//void setAnimationByIndex(int newIndex);
	//void changeAnimationTime(float newTime);
	//Animation* getCurrentAnimation();
	//Vector2D getWidthAndHeight();

	//bool collidedWithMouse(Vector2D loc);
	//bool OnScreen();

	//void shouldAnimate(bool shouldAnimate);

	//int getAnimationIndex() { return mAnimationIndex; }
	Vector2D getLoc() { return mLoc; }

	Boss(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, DataReader* data);
	//~Player();

	void setVelocity(Vector2D vel);

	bool myCollision(Unit* other);
	bool theirCollision(Unit* other);

	//for saving
	float getTimeSinceLastPattern() { return mSinceLastPattern; };
	void setTimeSinceLastPattern(float newTime) { mSinceLastPattern = newTime; };

	float getBossHealth() { return mBossHealth; };
	void setBossHealth(float newHealth) { mBossHealth = newHealth; };
private:

	float mBossHealth; 
	
	// TODO: make this data-driven
	float BASE_HEALTH = 50;

	float mSinceLastPattern = 0;
	float TIME_BETWEEN_PATTERNS = 10;
	float TIME_BEFORE_DOWNTIME = 4;
	float DIFFICULTY_PHASES = 5;

	EventSystem* pEventSystem;

};



