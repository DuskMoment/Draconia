#pragma once
#include "GameEvent.h"
class PlayerHealthEvent : public GameEvent
{
public:
	PlayerHealthEvent(const float& health);

	inline float getHealth() const { return mHealth; };

private:
	float mHealth;
};


