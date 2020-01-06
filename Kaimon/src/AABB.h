#pragma once
#include <vector>
#include "Vector3f.h"
#include "Entity.h"
#include "ICollider.h"

class AABB : public ICollider
{
public:
	AABB(Entity& entity);
	void update(Entity& entity);

	bool collideWith(ICollider* collider);
	bool collideWith(AABB* aabb);

	Vector3f getLocalMinVertex();
	Vector3f getLocalMaxVertex();

	Vector3f getWorldMinVertex();
	Vector3f getWorldMaxVertex();

	void setWorldMinVertex(Vector3f vec);
	void setWorldMaxVertex(Vector3f vec);

private:
	void calculateBoundingBox(std::vector<float>& vertices);

	Vector3f m_localMinVertex;
	Vector3f m_localMaxVertex;

	Vector3f m_worldMinVertex;
	Vector3f m_worldMaxVertex;
};