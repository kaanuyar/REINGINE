#include "Target.h"
#include "MathCalc.h"

Target::Target(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: CollideableEntity(rawEntity, texture, worldTranslation, worldRotation, worldScale), m_aabb(getVertices())
{
	m_aabb.update(*this);
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

void Target::restartPosition()
{
	do    
		setTranslationVector(Vector3f(MathCalc::generateRandomFloat(-9.75f, 9.75f), 0.0f, MathCalc::generateRandomFloat(-9.75f, 9.75f)));
	while (getTranslationVector().x < 1.25f && getTranslationVector().x > -1.25f && getTranslationVector().z < 1.25f && getTranslationVector().z > -1.25f);

	m_aabb.update(*this);
}

AABB& Target::getAABB()
{
	return m_aabb;
}
