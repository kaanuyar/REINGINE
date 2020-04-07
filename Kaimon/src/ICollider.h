#pragma once
#include <memory>

class AABB;
class OBB;
class ColliderMesh;


class ICollider
{
public:
	virtual ~ICollider() { }
	virtual bool collideWith(ICollider* collider) = 0;
	virtual bool collideWith(AABB* bbox) = 0;
	virtual bool collideWith(OBB* obb) = 0;

	virtual std::unique_ptr<ColliderMesh> createColliderMesh() = 0;
};