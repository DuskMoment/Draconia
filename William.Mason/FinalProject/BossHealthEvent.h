#pragma once
#include "GameEvent.h"
class BossHealthEvent : public GameEvent
{
public:
	BossHealthEvent(const float& health);

	inline float getHealth() const { return mHealth; };

private:
	float mHealth;
};


