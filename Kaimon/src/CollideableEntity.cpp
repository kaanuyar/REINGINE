#include "CollideableEntity.h"

CollideableEntity::CollideableEntity(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, float worldScale)
	: Entity(rawEntity, texture, worldTranslation, worldRotation, worldScale), m_aabb(getVertices())
{
	m_aabb.update(*this);
}

ICollider* CollideableEntity::getCollider()
{
	return &m_aabb;
}

#include <iostream>
void CollideableEntity::collisionResolution()
{
	std::cout << "collideableEntity: collision detected" << std::endl;
}
