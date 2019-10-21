#pragma once

#include "InteractableEntity.h"

class Player : public InteractableEntity
{
public:
	Player(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, float worldScale);

	void addRayCaster(RayCaster* rayCasterPtr);
	
	virtual EventHandler& getEventHandler();
	virtual void update(float deltaTime);
	virtual ICollider* getCollider();
	virtual void collisionResolution();

	// for testing 
	AABB& getAABB();
	bool moveTo(Vector3f pos, float deltaTime);

private:
	EventHandler m_eventHandler;

	void moveForward(float deltaTime);
	void moveBackward(float deltaTime);
	void moveRight(float deltaTime);
	void moveLeft(float deltaTime);
	void rotateAroundYAxis(float deltaTime);

	RayCaster* m_rayCasterPtr = nullptr;
	bool m_hasRayCaster = false;

	AABB m_aabb;
	Vector3f m_prevTranslationVector;
};
