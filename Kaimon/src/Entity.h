#pragma once
#include <vector>
#include "RawEntity.h"
#include "Vector3f.h"
#include "Texture.h"

class Entity
{
public:
	Entity(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale);
	virtual ~Entity();
	unsigned int getVaoID();
	unsigned int getTextureID();
	unsigned int getTextureUnit();
	void increaseTranslationVector(float dx, float dy, float dz);
	void increaseRotationVector(float dx, float dy, float dz);
	void setTranslationVector(Vector3f vec);
	Vector3f getTranslationVector();
	Vector3f getRotationVector();
	Vector3f getScaleVector();
	unsigned int getIndexCount();
	unsigned int getVertexCount();
	std::vector<float>& getVertices();

private:
	RawEntity& m_rawEntity;
	Texture& m_texture;
	Vector3f m_translationVector;
	Vector3f m_rotationVector;
	Vector3f m_scaleVector;
};