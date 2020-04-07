#pragma once

#include "AABB.h"
#include "CollideableEntity.h"
#include "Player.h"
#include "CollisionManager.h"

class Target : public CollideableEntity
{
public:
	Target(Model& model, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale);

	virtual ICollider* getCollider();
	virtual void collisionResolution(ICollideable* collideable);
	virtual void collisionResolution(Player* player);
	virtual void collisionResolution(Obstacle* obstacle);
	virtual void collisionResolution(Target* target);

	void resetTransform(Vector3f terrainMinVec, Vector3f terrainMaxVec);

	OBB& getOBB();
	virtual ColliderMesh* getColliderMesh();

private:
	OBB m_OBB;
	std::unique_ptr<ColliderMesh> m_colliderMesh;
	Vector3f m_edgeLengthVec;
};