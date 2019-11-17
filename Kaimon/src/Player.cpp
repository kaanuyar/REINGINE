#include "Player.h"
#include "Game.h"

Player::Player(Game* game, RawEntity & rawEntity, Texture & texture, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: InteractableEntity(rawEntity, texture, worldTranslation, worldRotation, worldScale), m_aabb(getVertices()),
		m_prevTranslationVector(worldTranslation.x, worldTranslation.y, worldTranslation.z), m_game(game)
{
}

void Player::update(float deltaTime)
{
	m_prevTranslationVector.setVector(getTranslationVector());

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
		else if (Event::MOUSE_BUTTON_RIGHT_PRESSED == it->state && m_hasRayCaster)
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
			else
			{
				if (!moveTo(Vector3f(it->x, it->y, it->z), deltaTime))
					it->isAlive = false;
			}
		}
		else
			it->isAlive = false;
	}
	m_eventHandler.deleteDeadEventsFromList();


	m_aabb.update(*this);
}


EventHandler& Player::getEventHandler()
{
	return m_eventHandler;
}

void Player::addRayCaster(RayCaster* rayCasterPtr)
{
	if (!m_hasRayCaster)
	{
		m_rayCasterPtr = rayCasterPtr;
		m_hasRayCaster = true;
	}

}


ICollider* Player::getCollider()
{
	return &m_aabb;
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
	m_aabb.update(*this);
	m_eventHandler.getEventList().clear();
}

void Player::collisionResolution(Target* target)
{
	setTranslationVector(Vector3f(0.0f, 0.0f, 0.0f));
	m_aabb.update(*this);
	m_eventHandler.getEventList().clear();

	m_game->onSuccess();
}

AABB& Player::getAABB()
{
	return m_aabb;
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

	if (length <= 0.1f)
		return false;

	float constant = 10.0f * deltaTime;
	Vector3f normPos(constant * deltaPos.x / length, constant * deltaPos.y / length, constant * deltaPos.z / length);

	increaseTranslationVector(normPos.x, normPos.y, normPos.z);
	return true;
}
