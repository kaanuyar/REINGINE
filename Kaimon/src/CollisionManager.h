#pragma once
#include <vector>
#include "ICollideable.h"
#include "Entity.h"

namespace CollisionManager
{
	void checkCollisions(std::vector<ICollideable*>& collideableList);
	void checkEntityCollisions(std::vector<Entity*>& entityList);
	bool checkCollisionsBool(std::vector<ICollideable*> collideableList);
}