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

// i want this class to inherit from unit :)
class PlayerFireball : public Unit
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

	PlayerFireball(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, float size);
	~PlayerFireball();
	//~Player();

	void setVelocity(Vector2D vel);

	bool myCollision(Unit* other);
	bool theirCollision(Unit* other);

	inline float getBulletDamage() { return mBulletDamage; }
private:

	float mBulletDamage = 1;
	// TODO: make this data-driven
	// Also TODO: make a projectile script that stores the damage number
};
