#pragma once
#include <vector>
#include "Vector3f.h"
#include "Entity.h"
#include "ICollider.h"
#include "Model.h"
#include "ColliderMesh.h"

class AABB : public ICollider
{
public:
	AABB(Entity& entity);
	void update(Entity& entity);

	bool collideWith(ICollider* collider);
	bool collideWith(AABB* aabb);
	bool collideWith(OBB* obb);

	std::unique_ptr<ColliderMesh> createColliderMesh();

	Vector3f getWorldMinVertex();
	Vector3f getWorldMaxVertex();

private:
	void AABB::calculateBoundingBox(Model& model);

	Vector3f m_localMinVertex;
	Vector3f m_localMaxVertex;

	Vector3f m_worldMinVertex;
	Vector3f m_worldMaxVertex;

	std::vector<Vector3f> m_localCornerVertices;
};