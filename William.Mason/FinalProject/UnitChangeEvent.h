#pragma once
#include "GameEvent.h"
#include <Vector2D.h>
class UnitChangeEvent : public GameEvent
{
public:
	UnitChangeEvent(const bool& shouldDelete, const Vector2D& loc);

	inline bool getShouldDelete() const { return mShouldDelete; };
	inline Vector2D getLoc() const { return mLoc; };
private:
	bool mShouldDelete = false;
	Vector2D mLoc = ZERO_VECTOR2D;
};

