#pragma once

#include "AABB.h"
#include "CollideableEntity.h"
#include "CollisionManager.h"
#include "Player.h"
#include "Target.h"

class Obstacle : public CollideableEntity
{
public:
	Obstacle(Model& model, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale);

	virtual ICollider* getCollider();
	virtual void collisionResolution(ICollideable* collideable);
	virtual void collisionResolution(Player* player);
	virtual void collisionResolution(Obstacle* obstacle);
	virtual void collisionResolution(Target* target);

	void restartPosition(Vector3f terrainMinVec, Vector3f terrainMaxVec);

	// for testing
	AABB& getAABB();
	// new stuff
	virtual Model& getCollisionModel();

private:
	AABB m_aabb;
	Model m_collisionModel;
	Vector3f m_edgeLengthVec;
};