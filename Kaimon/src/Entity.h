#pragma once
#include <vector>
#include "Model.h"
#include "Vector3f.h"


class Entity
{
public:
	Entity(Model& model, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale);
	virtual ~Entity();
	void increaseTranslationVector(float dx, float dy, float dz);
	void increaseRotationVector(float dx, float dy, float dz);
	void setTranslationVector(Vector3f vec);
	void setRotationVector(Vector3f vec);
	Vector3f getTranslationVector();
	Vector3f getRotationVector();
	Vector3f getScaleVector();
	Model& getModel();

private:
	Model& m_model;
	Vector3f m_translationVector;
	Vector3f m_rotationVector;
	Vector3f m_scaleVector;
};