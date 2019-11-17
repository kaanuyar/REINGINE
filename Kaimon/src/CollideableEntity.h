#pragma once
#include "Entity.h"
#include "ICollideable.h"

class CollideableEntity : public Entity, public ICollideable
{
public:
	CollideableEntity(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale);

	virtual ICollider* getCollider() = 0;
	virtual void collisionResolution(ICollideable* collideable) = 0;
	virtual void collisionResolution(Player* player) = 0;
	virtual void collisionResolution(Obstacle* obstacle) = 0;
	virtual void collisionResolution(Target* target) = 0;
};