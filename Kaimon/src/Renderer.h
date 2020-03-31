#pragma once
#include <vector>
#include "Entity.h"
#include "ShaderProgram.h"
#include "EntityShaderProgram.h"
#include "Camera.h"
#include "Window.h"
#include "ViewFrustum.h"
#include "CollideableEntity.h"


class Renderer
{
public:
	Renderer() : m_entityShader("src/shaders/VertexShader.vert", "src/shaders/FragmentShader.frag") {}
	void renderEntities(Camera& camera, ViewFrustum& frustum, Light& light, std::vector<Entity*>& entityList);

private:
	void renderMeshes(std::vector<std::unique_ptr<Mesh>>& meshes);

	EntityShaderProgram m_entityShader;
};