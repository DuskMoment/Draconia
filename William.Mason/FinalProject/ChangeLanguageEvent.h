#pragma once
#include "GameEvent.h"
class ChangeLanguageEvent : public GameEvent
{
public:
	ChangeLanguageEvent(int language);

	inline int getLanguage() const { return mLang; };
private:
	int mLang;
};

