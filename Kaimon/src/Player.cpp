#include "Player.h"
#include "Game.h"

#include <cmath>

Player::Player(Game* game, Model& model, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale, RayCaster* rayCaster)
	: InteractableEntity(model, worldTranslation, worldRotation, worldScale), m_OBB(*this), m_colliderMesh(m_OBB.createColliderMesh()),
	  m_prevTranslationVector(worldTranslation), m_prevRotationVector(worldRotation), m_game(game),
	  m_edgeLengthVec(m_OBB.getWorldMaxVertex() - m_OBB.getWorldMinVertex()), m_rayCasterPtr(rayCaster)
{
}

void Player::update(float deltaTime)
{
	m_prevTranslationVector = getTranslationVector();
	m_prevRotationVector = getRotationVector();

	std::vector<Event>& eventList = m_eventHandler.getEventList();
	if (eventList.empty())
		return;

	for (std::vector<Event>::iterator it = eventList.begin(); it != eventList.end(); ++it)
	{
		if (Event::KEY_W == it->state)
			moveForward(deltaTime);
		else if (Event::KEY_S == it->state)
			moveBackward(deltaTime);
		else if (Event::KEY_A == it->state)
			moveLeft(deltaTime);
		else if (Event::KEY_D == it->state)
			moveRight(deltaTime);
		else if (Event::KEY_R == it->state)
			rotateAroundYAxis(deltaTime);
		else if (Event::MOUSE_BUTTON_LEFT_PRESSED == it->state && m_rayCasterPtr)
		{
			if (!it->isProcessed)
			{
				Vector3f vec3 = m_rayCasterPtr->castRay(it->x, it->y);
				Vector3f interVec = m_rayCasterPtr->findIntersectionPointForXPlane(vec3);
				it->x = interVec.x;
				it->y = interVec.y;
				it->z = interVec.z;
				it->isProcessed = true;
			}
			if(it->isProcessed)
			{
				if (!moveTo(Vector3f(it->x, it->y, it->z), deltaTime))
					it->isAlive = false;
			}
		}
		else if (Event::MOVE_TO == it->state)
		{
			if (!moveTo(Vector3f(it->x, it->y, it->z), deltaTime))
				it->isAlive = false;
		}
		else if (Event::MOVE_TO_ANGLE == it->state)
		{
			moveToAngle(it->x, deltaTime);
		}
		else
			it->isAlive = false;
	}
	m_eventHandler.deleteDeadEventsFromList();

	m_OBB.update(*this);
}


EventHandler& Player::getEventHandler()
{
	return m_eventHandler;
}

void Player::resetTransform(Vector3f terrainMinVec, Vector3f terrainMaxVec)
{
	Vector3f minTranslationVec, maxTranslationVec;
	minTranslationVec.x = (terrainMinVec.x < 0) ? terrainMinVec.x + (m_edgeLengthVec.x / 2) : terrainMinVec.x - (m_edgeLengthVec.x / 2);
	minTranslationVec.z = (terrainMinVec.z < 0) ? terrainMinVec.z + (m_edgeLengthVec.z / 2) : terrainMinVec.z - (m_edgeLengthVec.z / 2);

	maxTranslationVec.x = (terrainMaxVec.x < 0) ? terrainMaxVec.x + (m_edgeLengthVec.x / 2) : terrainMaxVec.x - (m_edgeLengthVec.x / 2);
	maxTranslationVec.z = (terrainMaxVec.z < 0) ? terrainMaxVec.z + (m_edgeLengthVec.z / 2) : terrainMaxVec.z - (m_edgeLengthVec.z / 2);

	setTranslationVector(Vector3f(MathCalc::generateRandomFloat(minTranslationVec.x, maxTranslationVec.x), 0.0f, MathCalc::generateRandomFloat(minTranslationVec.z, maxTranslationVec.z)));
	setRotationVector(Vector3f(0.0f, 0.0f, 0.0f));
	m_OBB.update(*this);
	m_eventHandler.getEventList().clear();
}


ICollider* Player::getCollider()
{
	return &m_OBB;
}

void Player::collisionResolution(ICollideable* collideable)
{
	collideable->collisionResolution(this);
}

void Player::collisionResolution(Player* player)
{
}

void Player::collisionResolution(Obstacle* obstacle)
{
	setTranslationVector(m_prevTranslationVector);
	setRotationVector(m_prevRotationVector);
	m_OBB.update(*this);
	m_eventHandler.getEventList().clear();
}

void Player::collisionResolution(Target* target)
{
	m_game->onSuccess();
}

OBB& Player::getOBB()
{
	return m_OBB;
}

Vector3f Player::getEdgeLengthVec()
{
	return m_edgeLengthVec;
}

ColliderMesh* Player::getColliderMesh()
{
	return m_colliderMesh.get();
}


void Player::moveForward(float deltaTime)
{
	float dz = -10.0f * deltaTime;
	increaseTranslationVector(0.0f, 0.0f, dz);
}

void Player::moveBackward(float deltaTime)
{
	float dz = 10.0f * deltaTime;
	increaseTranslationVector(0.0f, 0.0f, dz);
}

void Player::moveRight(float deltaTime)
{
	float dx = 10.0f * deltaTime;
	increaseTranslationVector(dx, 0.0f, 0.0f);
}

void Player::moveLeft(float deltaTime)
{
	float dx = -10.0f * deltaTime;
	increaseTranslationVector(dx, 0.0f, 0.0f);
}

void Player::rotateAroundYAxis(float deltaTime)
{
	float dy = 60.0f * deltaTime;
	increaseRotationVector(0.0f, dy, 0.0f);
}

bool Player::moveTo(Vector3f pos, float deltaTime)
{
	Vector3f entityPos = getTranslationVector();
	Vector3f deltaPos(pos.x - entityPos.x, pos.y - entityPos.y, pos.z - entityPos.z);
	float length = 0.0f;
	length += pow(deltaPos.x, 2);
	length += pow(deltaPos.y, 2);
	length += pow(deltaPos.z, 2);
	length = sqrt(length);

	if (length <= 0.3)
		return false;

	float constant = 10.0f * deltaTime;
	Vector3f normPos(constant * deltaPos.x / length, constant * deltaPos.y / length, constant * deltaPos.z / length);

	constexpr double PI = 3.14159265358979323846;
	Vector3f normalVec(deltaPos.x / length, deltaPos.y / length, deltaPos.z / length);
	setRotationVector(Vector3f(0.0f, float(180.0f / PI * atan2(normalVec.x, normalVec.z)), 0.0f));

	increaseTranslationVector(normPos.x, normPos.y, normPos.z);
	return true;
}

void Player::moveToAngle(float angleInDegrees, float deltaTime)
{
	constexpr double PI = 3.14159265358979323846;
	Vector3f entityPos = getTranslationVector();
	float x = float(cos(angleInDegrees * PI / 180.0));
	float z = float(-sin(angleInDegrees * PI / 180.0));

	float constant = 10.0f * deltaTime;
	Vector3f normPos(constant * x, 0, constant * z);

	increaseTranslationVector(normPos.x, normPos.y, normPos.z);
}
