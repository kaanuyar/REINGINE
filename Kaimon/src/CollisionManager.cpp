#include "CollisionManager.h"

#include <iostream>
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
					collideableList[i]->collisionResolution();
					collideableList[j]->collisionResolution();
				}
				//else
					//std::cout << std::endl;
			}
		}
	}
}