#include "BossHealthEvent.h"

BossHealthEvent::BossHealthEvent(const float& health)
	:GameEvent(BOSS_HEALTH_EVENT), mHealth(health)
{

}
