#pragma once
#include "ICollider.h"

class Player;
class Obstacle;
class Target;

class ICollideable
{
public:
	virtual ~ICollideable() { }
	virtual ICollider* getCollider() = 0;

	virtual void collisionResolution(ICollideable* collideable) = 0;
	virtual void collisionResolution(Player* player) = 0;
	virtual void collisionResolution(Obstacle* obstacle) = 0;
	virtual void collisionResolution(Target* target) = 0;
};