#include "Target.h"
#include "MathCalc.h"

Target::Target(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: CollideableEntity(rawEntity, texture, worldTranslation, worldRotation, worldScale), m_aabb(*this),
	  m_edgeLengthVec(m_aabb.getWorldMaxVertex() - m_aabb.getWorldMinVertex())
{
}

ICollider* Target::getCollider()
{
	return &m_aabb;
}


void Target::collisionResolution(ICollideable* collideable)
{
	collideable->collisionResolution(this);
}

void Target::collisionResolution(Player* player)
{
}

void Target::collisionResolution(Obstacle* obstacle)
{
}

void Target::collisionResolution(Target* target)
{
}

void Target::restartPosition(Player& player)
{
	do
	{
		setTranslationVector(Vector3f(MathCalc::generateRandomFloat(-10.0f + m_edgeLengthVec.x / 2, 10.0f - m_edgeLengthVec.x / 2), 0.0f, MathCalc::generateRandomFloat(-10.0f + m_edgeLengthVec.x / 2, 10.0f - m_edgeLengthVec.x / 2)));
		m_aabb.update(*this);
	}
	while (CollisionManager::checkCollisionsBool({this, &player}));
}

AABB& Target::getAABB()
{
	return m_aabb;
}
