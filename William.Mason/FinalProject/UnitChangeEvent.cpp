#include "UnitChangeEvent.h"

UnitChangeEvent::UnitChangeEvent(const bool& shouldDelete, const Vector2D& loc)
	:GameEvent(UNIT_CHANGE_EVENT), mShouldDelete(shouldDelete), mLoc(loc)
{
}
