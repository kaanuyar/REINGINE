#include "CollideableEntity.h"

CollideableEntity::CollideableEntity(RawEntity& rawEntity, Texture& texture, Vector3f worldTranslation, Vector3f worldRotation, float worldScale)
	: Entity(rawEntity, texture, worldTranslation, worldRotation, worldScale)
{
}


