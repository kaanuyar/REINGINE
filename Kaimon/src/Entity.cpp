#include "Entity.h"
#include <GLAD/glad.h>

Entity::Entity(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: m_rawEntity(rawEntity), m_texture(texture), m_translationVector(worldTranslation), m_rotationVector(worldRotation), m_scaleVector(worldScale)
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

unsigned int Entity::getVaoID()
{
	return m_rawEntity.getVaoID();
}

unsigned int Entity::getTextureID()
{
	return m_texture.getTextureID();
}

unsigned int Entity::getTextureUnit()
{
	return m_texture.getTextureUnit();
}

unsigned int Entity::getIndexCount()
{
	return m_rawEntity.indexCount();
}

unsigned int Entity::getVertexCount()
{
	return m_rawEntity.vertexCount();
}

std::vector<float>& Entity::getVertices()
{
	return m_rawEntity.getVertices();
}
