#pragma once

#include "InteractableEntity.h"

class Game;

class Player : public InteractableEntity
{
public:
	Player(Game* game, RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale);

	void addRayCaster(RayCaster* rayCasterPtr);
	
	virtual EventHandler& getEventHandler();
	virtual void update(float deltaTime);
	virtual ICollider* getCollider();
	//virtual void collisionResolution();
	virtual void collisionResolution(ICollideable* collideable);
	virtual void collisionResolution(Player* player);
	virtual void collisionResolution(Obstacle* obstacle);
	virtual void collisionResolution(Target* target);

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
	Game* m_game;
};
