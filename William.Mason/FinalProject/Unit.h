#pragma once
#include <Trackable.h>
#include <Vector2D.h>
#include <vector>
#include <utility>
#include <Sprite.h>
#include <Animation.h>
class Sprite;
class Animation;
class GraphicsBuffer;
class GraphicsSystem;
class UnitManager;

class Unit : public Trackable
{
	friend UnitManager;
public:


	virtual void update(float deltaTime);//should be 16.7;
	void addAnimation(const Animation& newAnimaiton);
	void setPosition(const Vector2D& newLoc);

	void draw();
	void setAnimationByIndex(int newIndex);
	void changeAnimationTime(float newTime);
	Animation* getCurrentAnimation();
	Vector2D getWidthAndHeight();
	Vector2D getLoc() { return mLoc; };
	float getSize() { return mUnitSize; };

	Vector2D getHitboxLoc() { return (getLoc() + getSprite().getOffsetXY()); } // * mUnitSize?
	Vector2D getHitboxWidthHeight() { return (getWidthAndHeight() + getSprite().getWidthHeightHitBox()) * mUnitSize; }

	Sprite getSprite() { return mAnimationVec.at(mAnimationIndex).getCurrentSprite(); };

	bool collidedWithMouse(Vector2D loc);
	bool OnScreen();

	void shouldAnimate(bool shouldAnimate);

	int getAnimationIndex() { return mAnimationIndex; }

	

	// collision functions
	// return true if you want to self-destruct
	virtual bool myCollision(Unit* other); // you are the unit who is targeting other. 
	virtual bool theirCollision(Unit* other); // you are the unit who is being targeted by other
	
	//for saving
	int getMyTeam() { return mTeam; };
	int getTargetTeam() { return mTargetTeam; };
	void setMyTeam(int team) { mTeam = team; };
	Vector2D getVel() { return mVel; };
	float getSpeed() { return mSpeed; };
	
	// unprivating this for prototype purposes. should be private!!!!
	// update i think it needs to be unprivated for inherited objects?
	Unit(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, bool pooled = false);
	~Unit();

	bool mRenderInHUD = false; // this is a bit of a mess but hopefully obvious

protected:
	std::vector<Animation> mAnimationVec;
	int mAnimationIndex;
	bool mShouldAnimate = true;
	Vector2D mLoc;

	Vector2D mVel;
	float mSpeed;

	// the team of the unit. 
	int mTeam = 0;
	// the target team of the unit. it will only collide with units that have this team
	int mTargetTeam = 2;
	// if the unit goes offscreen, it is cleaned up only if this is true
	bool mDeleteOffscreen = true;
	bool mPooledObject = false;

	float mUnitSize = 2;

};

