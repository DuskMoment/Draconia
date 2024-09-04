#include "ChangeLanguageEvent.h"

ChangeLanguageEvent::ChangeLanguageEvent(int language)
	: GameEvent(CHANGE_LANGUAGE_EVENT), mLang(language)
{
}
