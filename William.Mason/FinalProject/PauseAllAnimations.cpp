#include "PauseAllAnimations.h"

PauseAllAnimations::PauseAllAnimations(const bool& shouldAnimate)
	:GameEvent(PAUSE_ANIMATION_EVENT), mShouldAnimate(shouldAnimate)
{
}
