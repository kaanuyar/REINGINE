#include "Obstacle.h"
#include "MathCalc.h"

Obstacle::Obstacle(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: CollideableEntity(rawEntity, texture, worldTranslation, worldRotation, worldScale), m_aabb(*this),
	  m_edgeLengthVec(m_aabb.getWorldMaxVertex() - m_aabb.getWorldMinVertex())
{
}


ICollider* Obstacle::getCollider()
{
	return &m_aabb;
}

void Obstacle::collisionResolution(ICollideable* collideable)
{
	collideable->collisionResolution(this);
}

void Obstacle::collisionResolution(Player* player)
{
}

void Obstacle::collisionResolution(Obstacle* obstacle)
{
}

void Obstacle::collisionResolution(Target* target)
{
}

void Obstacle::restartPosition(Player& player, Target& target)
{
	do
	{
		setTranslationVector(Vector3f(MathCalc::generateRandomFloat(-10.0f + m_edgeLengthVec.x / 2, 10.0f - m_edgeLengthVec.x / 2), 0.0f, MathCalc::generateRandomFloat(-10.0f + m_edgeLengthVec.x / 2, 10.0f - m_edgeLengthVec.x / 2)));
		m_aabb.update(*this);
	} while (CollisionManager::checkCollisionsBool({ this, &player, &target }));
}

AABB& Obstacle::getAABB()
{
	return m_aabb;
}
