#pragma once
#include <vector>
#include "Entity.h"
#include "ShaderProgram.h"
#include "EntityShaderProgram.h"
#include "Camera.h"
#include "Window.h"
#include "ViewFrustum.h"
#include <unordered_map>

namespace Renderer
{
	void renderEntities(EntityShaderProgram& entityShaderProgram, Camera& camera, ViewFrustum& frustum, std::vector<Entity*>& entityList);
	//std::unordered_map<RawEntity*, std::vector<Entity*>> processEntity(std::vector<Entity*>& entityList);

}