#include "Entity.h"

Entity::Entity(Model& model, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: m_model(model), m_translationVector(worldTranslation), m_rotationVector(worldRotation), m_scaleVector(worldScale)
{
}

Entity::~Entity()
{
}

Vector3f Entity::getTranslationVector()
{
	return m_translationVector;
}

Vector3f Entity::getRotationVector()
{
	return m_rotationVector;
}

Vector3f Entity::getScaleVector()
{
	return m_scaleVector;
}

Model& Entity::getModel()
{
	return m_model;
}


void Entity::increaseTranslationVector(float dx, float dy, float dz)
{
	m_translationVector.increasePosition(dx, dy, dz);
}

void Entity::increaseRotationVector(float dx, float dy, float dz)
{
	m_rotationVector.increasePosition(dx, dy, dz);
}


void Entity::setTranslationVector(Vector3f vec)
{
	m_translationVector.setVector(vec);
}

