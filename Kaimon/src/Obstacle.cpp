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

void Obstacle::restartPosition(Vector3f terrainMinVec, Vector3f terrainMaxVec)
{
	Vector3f minTranslationVec, maxTranslationVec;
	minTranslationVec.x = (terrainMinVec.x < 0) ? terrainMinVec.x + (m_edgeLengthVec.x / 2) : terrainMinVec.x - (m_edgeLengthVec.x / 2);
	minTranslationVec.z = (terrainMinVec.z < 0) ? terrainMinVec.z + (m_edgeLengthVec.z / 2) : terrainMinVec.z - (m_edgeLengthVec.z / 2);

	maxTranslationVec.x = (terrainMaxVec.x < 0) ? terrainMaxVec.x + (m_edgeLengthVec.x / 2) : terrainMaxVec.x - (m_edgeLengthVec.x / 2);
	maxTranslationVec.z = (terrainMaxVec.z < 0) ? terrainMaxVec.z + (m_edgeLengthVec.z / 2) : terrainMaxVec.z - (m_edgeLengthVec.z / 2);

	setTranslationVector(Vector3f(MathCalc::generateRandomFloat(minTranslationVec.x, maxTranslationVec.x), 0.0f, MathCalc::generateRandomFloat(minTranslationVec.z, maxTranslationVec.z)));
	m_aabb.update(*this);
}

AABB& Obstacle::getAABB()
{
	return m_aabb;
}
