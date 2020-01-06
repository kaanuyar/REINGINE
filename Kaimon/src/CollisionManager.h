#pragma once
#include <vector>
#include "ICollideable.h"

namespace CollisionManager
{
	void checkCollisions(std::vector<ICollideable*>& collideableList);
	bool checkCollisionsBool(std::vector<ICollideable*> collideableList);
}