#include "DiffucltyChangeEvent.h"

DiffucltyChangeEvent::DiffucltyChangeEvent(int diff)
	:GameEvent(DIFFICULTY_CHANGE_EVENT) 
{
	mDiffculty = diff;
}
