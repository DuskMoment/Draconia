#pragma once
#include <Trackable.h>
#include <Vector2D.h>
#include <vector>
#include <utility>
#include "PlayerDirectionEvent.h"
#include "Unit.h"

class Sprite;
class Animation;
class GraphicsBuffer;
class GraphicsSystem;
class UnitManager;
class DataReader;

// i want this class to inherit from unit :)
class Tailwind : public Unit
{
	friend UnitManager;
public:
	void update(float deltaTime);//should be 16.7;

	Vector2D getLoc() { return mLoc; }

	Tailwind(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, DataReader* data);
	//~Player();

	bool myCollision(Unit* other);
	bool theirCollision(Unit* other);
private:
	bool tailwindUsed = false;
	float TAILWIND_SPEED = 2;

	int TAILWIND_HEAL;
	int TAILWIND_OVERHEAL;
};

