#include "InteractableEntity.h"

#include <iostream>

InteractableEntity::InteractableEntity(Model& model, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: CollideableEntity(model, worldTranslation, worldRotation, worldScale)
{
}

InteractableEntity::~InteractableEntity()
{
}
