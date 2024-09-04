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
class DataReader;

// i want this class to inherit from unit :)
class Player : public Unit
{
	friend UnitManager;
public:


	void update(float deltaTime);//should be 16.7;
	//void draw();
	//void addAnimation(const Animation& newAnimaiton);
	//void setPosition(const Vector2D& newLoc);

	
	//void setAnimationByIndex(int newIndex);
	//void changeAnimationTime(float newTime);
	//Animation* getCurrentAnimation();
	//Vector2D getWidthAndHeight();

	//bool collidedWithMouse(Vector2D loc);
	//bool OnScreen();

	//void shouldAnimate(bool shouldAnimate);

	//int getAnimationIndex() { return mAnimationIndex; }
	Vector2D getLoc() { return mLoc; }

	Player(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, DataReader* data);
	~Player();

	void setVelocity(Vector2D vel);
	void setInput(Input dir, bool val);

	bool myCollision(Unit* other);
	bool theirCollision(Unit* other);

	Vector2D projectileSpawnLocation() { return Vector2D((mLoc.getX() + (getWidthAndHeight().getX() / getSpawnLocOffset())), mLoc.getY() + (getWidthAndHeight().getY() / getSpawnLocOffset())); }

	void takeDamage(int value);
	void applyTailwind(float value);

	int getSpawnLocOffset() { return 2 / mUnitSize; }

	//for saving 
	int getPlayerHealth() { return mHealth; };
	void setPlayerHealth(int health) { mHealth = health; };
	bool isAboveMaxHealth() { return mHealth >= BASE_HEALTH; }
private:

	//std::vector<Animation> mAnimationVec;
	//int mAnimationIndex;
	//bool mShouldAnimate = true;
	//Vector2D mLoc;

	//Vector2D mVel;
	//int mSpeed;

	bool mUp;
	bool mLeft;
	bool mDown;
	bool mRight;

	bool mShoot;
	bool mLastShoot;

	float mChargeTime = 0;

	float BASE_SPEED = 1;
	float MAX_SPEED = 3.5;
	float SPEED_DECAY = 2;
	float FIREBALL_MIN_CHARGE_TIME = 0.5f;
	float FIREBALL_MAX_CHARGE_TIME = 1.5f;
	float FIREBALL_BASE_SIZE_MODIFIER = 0.6f;

	int mHealth;

	// TODO: make this data-driven
	float BASE_HEALTH = 50;
};


