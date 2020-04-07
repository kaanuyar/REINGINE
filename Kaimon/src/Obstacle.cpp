#include "Obstacle.h"
#include "MathCalc.h"

Obstacle::Obstacle(Model& model, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: CollideableEntity(model, worldTranslation, worldRotation, worldScale), m_OBB(*this), m_colliderMesh(m_OBB.createColliderMesh()),
	  m_edgeLengthVec(m_OBB.getWorldMaxVertex() - m_OBB.getWorldMinVertex())
{
}


ICollider* Obstacle::getCollider()
{
	return &m_OBB;
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

void Obstacle::resetTransform(Vector3f terrainMinVec, Vector3f terrainMaxVec)
{
	Vector3f minTranslationVec, maxTranslationVec;
	minTranslationVec.x = (terrainMinVec.x < 0) ? terrainMinVec.x + (m_edgeLengthVec.x / 2) : terrainMinVec.x - (m_edgeLengthVec.x / 2);
	minTranslationVec.z = (terrainMinVec.z < 0) ? terrainMinVec.z + (m_edgeLengthVec.z / 2) : terrainMinVec.z - (m_edgeLengthVec.z / 2);

	maxTranslationVec.x = (terrainMaxVec.x < 0) ? terrainMaxVec.x + (m_edgeLengthVec.x / 2) : terrainMaxVec.x - (m_edgeLengthVec.x / 2);
	maxTranslationVec.z = (terrainMaxVec.z < 0) ? terrainMaxVec.z + (m_edgeLengthVec.z / 2) : terrainMaxVec.z - (m_edgeLengthVec.z / 2);

	setTranslationVector(Vector3f(MathCalc::generateRandomFloat(minTranslationVec.x, maxTranslationVec.x), 0.0f, MathCalc::generateRandomFloat(minTranslationVec.z, maxTranslationVec.z)));
	setRotationVector(Vector3f(0.0f, 0.0f, 0.0f));
	m_OBB.update(*this);
}

OBB& Obstacle::getOBB()
{
	return m_OBB;
}

ColliderMesh* Obstacle::getColliderMesh()
{
	return m_colliderMesh.get();
}
