#pragma once
#include <vector>
#include "ICollideable.h"

namespace CollisionManager
{
	void checkCollisions(std::vector<ICollideable*>& collideableList);
}