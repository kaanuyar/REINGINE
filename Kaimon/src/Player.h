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

	void resetTransform(Vector3f terrainMinVec, Vector3f terrainMaxVec);

	OBB& getOBB();
	Vector3f getEdgeLengthVec();

	virtual ColliderMesh* getColliderMesh();

private:
	EventHandler m_eventHandler;
	OBB m_OBB;
	std::unique_ptr<ColliderMesh> m_colliderMesh;

	void moveForward(float deltaTime);
	void moveBackward(float deltaTime);
	void moveRight(float deltaTime);
	void moveLeft(float deltaTime);
	void rotateAroundYAxis(float deltaTime);
	bool moveTo(Vector3f pos, float deltaTime);
	void moveToAngle(float angleInDegrees, float deltaTime);

	RayCaster* m_rayCasterPtr = nullptr;
	Vector3f m_prevTranslationVector;
	Vector3f m_prevRotationVector;
	Vector3f m_edgeLengthVec;
	Game* m_game;
};
