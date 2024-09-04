#pragma once
#include "GameEvent.h"
class DiffucltyChangeEvent : public GameEvent
{
public:
	DiffucltyChangeEvent(int diff);
	inline int getDifficulty() const { return mDiffculty; };

private:
	int mDiffculty;
};

