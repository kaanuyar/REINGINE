#pragma once
#include "Entity.h"
#include "ICollideable.h"

class CollideableEntity : public Entity, public ICollideable
{
public:
	CollideableEntity(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, float worldScale);

	virtual ICollider* getCollider() = 0;
	virtual void collisionResolution() = 0;
};