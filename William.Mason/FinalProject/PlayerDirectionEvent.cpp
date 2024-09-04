#include "PlayerDirectionEvent.h"

PlayerDirectionEvent::PlayerDirectionEvent(const Input& dir, const bool& go)
	: GameEvent(PLAYER_DIRECTION_EVENT), mDir(dir), mGo(go)
{
}
