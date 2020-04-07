#pragma once

#include <vector>
#include "Vector3f.h"
#include "Entity.h"
#include "ICollider.h"
#include "Model.h"
#include "ColliderMesh.h"

class OBB : public ICollider
{
public:
	OBB(Entity& entity);
	void update(Entity& entity);

	bool collideWith(ICollider* collider);
	bool collideWith(AABB* aabb);
	bool collideWith(OBB* obb);

	std::unique_ptr<ColliderMesh> createColliderMesh();

	std::vector<Vector3f>& getWorldCornerVertices();
	std::vector<Vector3f>& getWorldFaceNormals();
	Vector3f getWorldMinVertex();
	Vector3f getWorldMaxVertex();

private:
	void calculateBoundingBox(Model& model);

	bool isIntersectOBB(std::vector<Vector3f>& firstWorldCorners, std::vector<Vector3f>& secondWorldCorners, Vector3f& axis);

	Vector3f m_localMinVertex;
	Vector3f m_localMaxVertex;
	Vector3f m_worldMinVertex;
	Vector3f m_worldMaxVertex;

	std::vector<Vector3f> m_localCornerVertices;
	std::vector<Vector3f> m_worldCornerVertices;
	std::vector<Vector3f> m_localFaceNormals; // x y z its always basis vectors for aabb case, just need to update it with transformation matrix each frame to get the worldFaceNormals
	std::vector<Vector3f> m_worldFaceNormals;
};