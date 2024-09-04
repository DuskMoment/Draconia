#include "ChangePointEvent.h"

ChangePointEvent::ChangePointEvent(const bool& isNegitive)
	:GameEvent(CHANGE_POINT_EVENT), mIsNegitive(isNegitive)
{
}
