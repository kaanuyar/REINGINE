#pragma once

class AABB;

class ICollider
{
public:
	virtual ~ICollider() { }
	virtual bool collideWith(ICollider* collider) = 0;
	virtual bool collideWith(AABB* bbox) = 0;
};