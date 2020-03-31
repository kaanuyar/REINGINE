#pragma once
#include "Entity.h"
#include "ICollideable.h"
#include "Model.h"

class CollideableEntity : public Entity, public ICollideable
{
public:
	CollideableEntity(Model& model, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale);

	virtual ~CollideableEntity();
	virtual ICollider* getCollider() = 0;
	virtual void collisionResolution(ICollideable* collideable) = 0;
	virtual void collisionResolution(Player* player) = 0;
	virtual void collisionResolution(Obstacle* obstacle) = 0;
	virtual void collisionResolution(Target* target) = 0;

	// new stuff
	virtual Model& getCollisionModel() = 0;
};