#pragma once
#include "GameEvent.h"
#include <Vector2D.h>

enum Input { Up, Down, Left, Right, Shoot};

class PlayerDirectionEvent : public GameEvent
{
public:
	PlayerDirectionEvent(const Input& dir, const bool& go);

	inline Input getDir() const { return mDir; };
	inline bool getGo() const { return mGo; }; 
;private:
	Input mDir = Up;
	bool mGo = false;
};

