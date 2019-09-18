#pragma once
#include "ICollider.h"


class ICollideable
{
public:
	virtual ~ICollideable() { }
	virtual ICollider* getCollider() = 0;
	virtual void collisionResolution() = 0;
};