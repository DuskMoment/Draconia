#pragma once
#include "GameEvent.h"
class ChangePointEvent: public GameEvent
{
public:
	ChangePointEvent(const bool& isNegitive);

	inline bool getIsNegitive() const { return mIsNegitive; };
private:
	bool mIsNegitive;
};

