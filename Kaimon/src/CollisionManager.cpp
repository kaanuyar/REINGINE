#include "CollisionManager.h"

namespace CollisionManager
{
	void checkCollisions(std::vector<ICollideable*>& collideableList)
	{
		for (unsigned int i = 0; i < collideableList.size(); i++)
		{
			for (unsigned int j = i + 1; j < collideableList.size(); j++)
			{
				if (collideableList[i]->getCollider()->collideWith(collideableList[j]->getCollider()))
				{
					collideableList[i]->collisionResolution(collideableList[j]);
					collideableList[j]->collisionResolution(collideableList[i]);
				}
			}
		}
	}

	void checkEntityCollisions(std::vector<Entity*>& entityList)
	{
		std::vector<ICollideable*> collideableList;
		for (Entity* entity : entityList)
		{
			ICollideable* collideable = nullptr;
			if (collideable = dynamic_cast<ICollideable*>(entity))
				collideableList.push_back(collideable);
		}

		for (unsigned int i = 0; i < collideableList.size(); i++)
		{
			for (unsigned int j = i + 1; j < collideableList.size(); j++)
			{
				if (collideableList[i]->getCollider()->collideWith(collideableList[j]->getCollider()))
				{
					collideableList[i]->collisionResolution(collideableList[j]);
					collideableList[j]->collisionResolution(collideableList[i]);
				}
			}
		}
	}

	bool checkCollisionsBool(std::vector<ICollideable*> collideableList)
	{
		for (unsigned int i = 0; i < collideableList.size(); i++)
		{
			for (unsigned int j = i + 1; j < collideableList.size(); j++)
			{
				if (collideableList[i]->getCollider()->collideWith(collideableList[j]->getCollider()))
					return true;
			}
		}

		return false;
	}
}