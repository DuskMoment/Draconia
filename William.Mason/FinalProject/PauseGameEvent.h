#pragma once
#include "GameEvent.h"
class PauseGameEvent : public GameEvent
{
public:
	PauseGameEvent(const bool& shouldPause);

	inline bool getShouldQuit() const { return mShouldQuit; };

private:

	bool mShouldQuit = false;
};

