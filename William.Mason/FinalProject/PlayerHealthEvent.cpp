#include "PlayerHealthEvent.h"

PlayerHealthEvent::PlayerHealthEvent(const float& health)
	:GameEvent(PLAYER_HEALTH_EVENT), mHealth(health)
{

}
