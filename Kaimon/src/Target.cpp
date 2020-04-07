#include "Target.h"
#include "MathCalc.h"

Target::Target(Model& model, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: CollideableEntity(model, worldTranslation, worldRotation, worldScale), m_OBB(*this), m_colliderMesh(m_OBB.createColliderMesh()),
	  m_edgeLengthVec(m_OBB.getWorldMaxVertex() - m_OBB.getWorldMinVertex())
{
}

ICollider* Target::getCollider()
{
	return &m_OBB;
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

void Target::resetTransform(Vector3f terrainMinVec, Vector3f terrainMaxVec)
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

OBB& Target::getOBB()
{
	return m_OBB;
}

ColliderMesh* Target::getColliderMesh()
{
	return m_colliderMesh.get();
}
