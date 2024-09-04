#include "Animation.h"
#include "Sprite.h"
#include <vector>

//might have to change to const?
Animation::Animation(std::vector<Sprite> spriteVec, float time, bool loop)
{
	mpSpriteVec = spriteVec;
	mLoop = loop;
	mTimePerSprite = mFrameMilliseconds/time;
	mCurrSpriteIndex = 0;
	mTimeRemaining = mTimePerSprite;
}

Animation::~Animation()
{
	//dont delete mSpriteVector ownership should be in game where the sprite is created
}

void Animation::update(float deltaTime)
{
	if (mAnimating)
	{
		//get remaing time
		mTimeRemaining -= deltaTime;

		if (mTimeRemaining <= 0)
		{

			mCurrSpriteIndex++;
			mTimeRemaining = mTimePerSprite;

			//the <= is causeing build warnings why
			if (mpSpriteVec.size() <= (unsigned int)mCurrSpriteIndex && mLoop)
			{
				mCurrSpriteIndex = 0;

			}
			else if (mpSpriteVec.size() <= (unsigned int)mCurrSpriteIndex && !mLoop)
			{
				mCurrSpriteIndex--;
			}
		}

	}
	
}

void Animation::setSpeed(float time)
{

	mTimePerSprite = mFrameMilliseconds/time;
}

float Animation::getTimeRemaining()
{
	return mTimeRemaining;
}

void Animation::setAnimating(bool shouldAnimate)
{
	mAnimating = shouldAnimate;
}

Sprite Animation::getCurrentSprite()
{
	return mpSpriteVec.at(mCurrSpriteIndex);
}
