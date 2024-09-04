#pragma once
#include <Trackable.h>
#include <vector>
#include "Sprite.h"

class Sprite;//forward declaration

class Animation : public Trackable
{
public:
	Animation(std::vector<Sprite> spriteVec, float time, bool loop);//get animation data throught the constructor
	~Animation();

	void update(float deltaTime);
	void setSpeed(float time);
	float getTimeRemaining();

	void setAnimating(bool shouldAnimate);

	Sprite getCurrentSprite();

private:
	std::vector<Sprite> mpSpriteVec; 
	

	int mCurrSpriteIndex;
	bool mLoop;
	bool mAnimating = true;

	//animation speed
	float mTimePerSprite;
	float mTimeRemaining;

	int mFrameMilliseconds = 1000;

};

