#include "PauseGameEvent.h"

PauseGameEvent::PauseGameEvent(const bool& shouldPause)
	: GameEvent(PAUSE_GAME_EVENT), mShouldQuit(shouldPause)
{
}
