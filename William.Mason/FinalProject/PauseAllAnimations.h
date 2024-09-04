#pragma once
#include "GameEvent.h"

class PauseAllAnimations : public GameEvent
{
public:
	PauseAllAnimations(const bool& shouldAnimate);

	inline bool getShouldAnimate() const { return mShouldAnimate; };
private:

	bool mShouldAnimate = true;
};

