#pragma once

#include "AABB.h"
#include "CollideableEntity.h"

class Obstacle : public CollideableEntity
{
public:
	Obstacle(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, float worldScale);

	virtual ICollider* getCollider();
	virtual void collisionResolution();

	// for testing
	AABB& getAABB();

private:
	AABB m_aabb;
};