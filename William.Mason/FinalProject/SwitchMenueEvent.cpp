#include "SwitchMenueEvent.h"

SwitchMenueEvent::SwitchMenueEvent(bool isRight)
	:GameEvent(SWITCH_MENUE_EVENT)
{
	mIsRight = isRight;
}
