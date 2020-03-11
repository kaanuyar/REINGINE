#include "Renderer.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

void Renderer::renderEntities(EntityShaderProgram& entityShaderProgram, Camera& camera, ViewFrustum& frustum, std::vector<Entity*>& entityList)
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	entityShaderProgram.useProgram();

	entityShaderProgram.loadProjectionMatrix(frustum);
	entityShaderProgram.loadViewPos(camera);
	entityShaderProgram.loadViewMatrix(camera);

	//std::unordered_map<RawEntity*, std::vector<Entity*>> umap = processEntity(entityList);

	//for (auto it = umap.begin(); it != umap.end(); ++it)
	//{
	//	RawEntity* entity = it->first;

	//	glActiveTexture(GL_TEXTURE0); // active proper texture unit before binding
	//	glBindTexture(GL_TEXTURE_2D, entity->getTextureID());
	//	entityShaderProgram.loadTexture(0);
	//	glBindVertexArray(entity->getVaoID());

	//}

	for (Entity* entity : entityList)
	{
		entityShaderProgram.loadTransformationMatrix(*entity);
		entityShaderProgram.loadTexture(0);
		glActiveTexture(GL_TEXTURE0); // active proper texture unit before binding
		glBindTexture(GL_TEXTURE_2D, entity->getTextureID());

		glBindVertexArray(entity->getVaoID());
		glDrawElements(GL_TRIANGLES, entity->getIndexCount(), GL_UNSIGNED_INT, 0);
	}

	entityShaderProgram.stopProgram();
}

std::unordered_map<RawEntity*, std::vector<Entity*>> Renderer::processEntity(std::vector<Entity*>& entityList)
{
	std::unordered_map<RawEntity*, std::vector<Entity*>> umap;

	for (Entity* entity : entityList)
	{
		RawEntity& rawEntity = entity->getRawEntity();

		if (umap.find(&rawEntity) == umap.end())
			umap[&rawEntity] = { entity };
		else
			umap[&rawEntity].push_back(entity);
	}

	return umap;
}

