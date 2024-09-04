#pragma once
#include "GameEvent.h"
class SwitchMenueEvent : public GameEvent
{
public:
	SwitchMenueEvent(bool isRight);

	inline bool getIsRight() const { return mIsRight; };
private:
	bool mIsRight;
};

