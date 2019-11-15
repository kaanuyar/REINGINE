#include "InteractableEntity.h"

#include <iostream>

InteractableEntity::InteractableEntity(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: CollideableEntity(rawEntity, texture, worldTranslation, worldRotation, worldScale)
{
}
