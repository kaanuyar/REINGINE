#include "Obstacle.h"
#include "MathCalc.h"

Obstacle::Obstacle(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: CollideableEntity(rawEntity, texture, worldTranslation, worldRotation, worldScale), m_aabb(getVertices())
{
	m_aabb.update(*this);
}


ICollider* Obstacle::getCollider()
{
	return &m_aabb;
}

void Obstacle::collisionResolution(ICollideable* collideable)
{
	collideable->collisionResolution(this);
}

void Obstacle::collisionResolution(Player* player)
{
}

void Obstacle::collisionResolution(Obstacle* obstacle)
{
}

void Obstacle::collisionResolution(Target* target)
{
}

AABB& Obstacle::getAABB()
{
	return m_aabb;
}
