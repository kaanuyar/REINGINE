#include "Obstacle.h"

Obstacle::Obstacle(RawEntity & rawEntity, Texture & texture, Vector3f worldTranslation, Vector3f worldRotation, float worldScale)
	: CollideableEntity(rawEntity, texture, worldTranslation, worldRotation, worldScale), m_aabb(getVertices())
{
	m_aabb.update(*this);
}


ICollider* Obstacle::getCollider()
{
	return &m_aabb;
}

#include <iostream>
void Obstacle::collisionResolution()
{
	std::cout << "collideableEntity: collision detected" << std::endl;
}

AABB& Obstacle::getAABB()
{
	return m_aabb;
}
