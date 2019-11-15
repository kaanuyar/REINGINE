#include "CollideableEntity.h"

CollideableEntity::CollideableEntity(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: Entity(rawEntity, texture, worldTranslation, worldRotation, worldScale)
{
}


