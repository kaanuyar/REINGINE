#pragma once
#include "Entity.h"
#include "ICollideable.h"
#include "AABB.h"

class CollideableEntity : public Entity, public ICollideable
{
public:
	CollideableEntity(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, float worldScale);

	ICollider* getCollider();
	void collisionResolution();

private:
	AABB m_aabb;
};