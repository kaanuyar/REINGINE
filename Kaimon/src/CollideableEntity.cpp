#include "CollideableEntity.h"

CollideableEntity::CollideableEntity(Model& model, Vector3f worldTranslation, Vector3f worldRotation, Vector3f worldScale)
	: Entity(model, worldTranslation, worldRotation, worldScale)
{
}

CollideableEntity::~CollideableEntity()
{
}
