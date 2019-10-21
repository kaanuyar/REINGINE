#pragma once
#include <vector>
#include "Entity.h"
#include "EventHandler.h"
#include "Event.h"
#include "IUpdatable.h"
#include "RayCaster.h"
#include "AABB.h"

#include "CollideableEntity.h"

class InteractableEntity : public CollideableEntity, public IUpdatable
{
public:
	InteractableEntity(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, float worldScale);

	EventHandler& getEventHandler() = 0;
	virtual void update(float deltaTime) = 0;
	virtual ICollider* getCollider() = 0;
	virtual void collisionResolution() = 0;
};	