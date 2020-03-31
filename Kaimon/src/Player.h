#pragma once

#include "InteractableEntity.h"

class Game;

class Player : public InteractableEntity
{
public:
	Player(Game* game, Model& model, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale, RayCaster* rayCaster = nullptr);
	
	virtual EventHandler& getEventHandler();
	virtual void update(float deltaTime);
	virtual ICollider* getCollider();
	virtual void collisionResolution(ICollideable* collideable);
	virtual void collisionResolution(Player* player);
	virtual void collisionResolution(Obstacle* obstacle);
	virtual void collisionResolution(Target* target);

	void restartPosition(Vector3f terrainMinVec, Vector3f terrainMaxVec);

	// for testing 
	AABB& getAABB();
	Vector3f getEdgeLengthVec();

	// new stuff
	virtual Model& getCollisionModel();

private:
	EventHandler m_eventHandler;
	AABB m_aabb;
	Model m_collisionModel;

	void moveForward(float deltaTime);
	void moveBackward(float deltaTime);
	void moveRight(float deltaTime);
	void moveLeft(float deltaTime);
	void rotateAroundYAxis(float deltaTime);
	bool moveTo(Vector3f pos, float deltaTime);
	void moveToAngle(float angleInDegrees, float deltaTime);

	RayCaster* m_rayCasterPtr = nullptr;
	Vector3f m_prevTranslationVector;
	Vector3f m_edgeLengthVec;
	Game* m_game;
};
