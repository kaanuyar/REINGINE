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

	std::vector<std::string> texturePathList;
	int index = 0;
	for (Entity* entity : entityList)
	{
		entityShaderProgram.loadTransformationMatrix(*entity);
		if (std::find(texturePathList.begin(), texturePathList.end(), entity->getTexturePath()) == texturePathList.end())
		{
			glActiveTexture(GL_TEXTURE0 + index); // active proper texture unit before binding
			glBindTexture(GL_TEXTURE_2D, entity->getTextureID());
			entityShaderProgram.loadTexture(index);
			texturePathList.push_back(entity->getTexturePath());
			index++;
		}

		glBindVertexArray(entity->getVaoID());
		glDrawElements(GL_TRIANGLES, entity->getIndexCount(), GL_UNSIGNED_INT, 0);
	}

	entityShaderProgram.stopProgram();
}

