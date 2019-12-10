#pragma once

#include "InteractableEntity.h"

class Game;

class Player : public InteractableEntity
{
public:
	Player(Game* game, RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale);
	
	virtual EventHandler& getEventHandler();
	virtual void update(float deltaTime);
	virtual ICollider* getCollider();
	virtual void collisionResolution(ICollideable* collideable);
	virtual void collisionResolution(Player* player);
	virtual void collisionResolution(Obstacle* obstacle);
	virtual void collisionResolution(Target* target);

	void addRayCaster(RayCaster* rayCasterPtr);
	void restartPosition();

	// for testing 
	AABB& getAABB();

private:
	EventHandler m_eventHandler;

	void moveForward(float deltaTime);
	void moveBackward(float deltaTime);
	void moveRight(float deltaTime);
	void moveLeft(float deltaTime);
	void rotateAroundYAxis(float deltaTime);
	bool moveTo(Vector3f pos, float deltaTime);
	void moveToAngle(float angleInDegrees, float deltaTime);

	RayCaster* m_rayCasterPtr = nullptr;
	bool m_hasRayCaster = false;

	AABB m_aabb;
	Vector3f m_prevTranslationVector;
	Game* m_game;
};
