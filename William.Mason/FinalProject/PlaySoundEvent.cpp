#include "PlaySoundEvent.h"

PlaySoundEvent::PlaySoundEvent(const std::string& key)
	:GameEvent(PLAY_SOUND_EVENT), mKey(key)
{
}
