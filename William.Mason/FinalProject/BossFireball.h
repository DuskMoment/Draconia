#include "Unit.h"

class Sprite;
class Animation;
class GraphicsBuffer;
class GraphicsSystem;
class UnitManager;

// i want this class to inherit from unit :)
class BossFireball : public Unit
{
	friend UnitManager;
public:

	void update(float deltaTime);//should be 16.7
	Vector2D getLoc() { return mLoc; }

	BossFireball(const Vector2D& loc, std::vector<Animation> animations, const Vector2D& vel, int speed, float size);
	~BossFireball();
	//~Player();

	void setVelocity(Vector2D vel);

	bool myCollision(Unit* other);
	bool theirCollision(Unit* other);

	inline float getBulletDamage() { return mBulletDamage; }
private:

	float mBulletDamage = 1;
	// TODO: make this data-driven
	// Also TODO: make a projectile script that stores the damage number
};

