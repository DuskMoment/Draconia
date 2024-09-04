#pragma once
#include "GameEvent.h"
class PlaySoundEvent : public GameEvent
{
public:
	PlaySoundEvent(const std::string& key);

	inline std::string getKey() const { return mKey; };

private:
	std::string mKey;
};

