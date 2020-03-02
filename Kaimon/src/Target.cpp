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

void Target::restartPosition(Vector3f terrainMinVec, Vector3f terrainMaxVec)
{
	Vector3f minTranslationVec, maxTranslationVec;
	minTranslationVec.x = (terrainMinVec.x < 0) ? terrainMinVec.x + (m_edgeLengthVec.x / 2) : terrainMinVec.x - (m_edgeLengthVec.x / 2);
	minTranslationVec.z = (terrainMinVec.z < 0) ? terrainMinVec.z + (m_edgeLengthVec.z / 2) : terrainMinVec.z - (m_edgeLengthVec.z / 2);

	maxTranslationVec.x = (terrainMaxVec.x < 0) ? terrainMaxVec.x + (m_edgeLengthVec.x / 2) : terrainMaxVec.x - (m_edgeLengthVec.x / 2);
	maxTranslationVec.z = (terrainMaxVec.z < 0) ? terrainMaxVec.z + (m_edgeLengthVec.z / 2) : terrainMaxVec.z - (m_edgeLengthVec.z / 2);

	setTranslationVector(Vector3f(MathCalc::generateRandomFloat(minTranslationVec.x, maxTranslationVec.x), 0.0f, MathCalc::generateRandomFloat(minTranslationVec.z, maxTranslationVec.z)));
	m_aabb.update(*this);
}

AABB& Target::getAABB()
{
	return m_aabb;
}
