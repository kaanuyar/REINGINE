#include "Renderer.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>


void Renderer::renderEntities(Camera& camera, ViewFrustum& frustum, Light& light, std::vector<Entity*>& entityList)
{
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_entityShader.useProgram();

	m_entityShader.loadProjectionMatrix(frustum);
	m_entityShader.loadViewPos(camera);
	m_entityShader.loadViewMatrix(camera);
	m_entityShader.loadLight(light);

	for (Entity* entity : entityList)
	{
		m_entityShader.loadTransformationMatrix(*entity);
		renderMeshes(entity->getModel().getMeshes());

		CollideableEntity* collideableEntity = nullptr;
		if (collideableEntity = dynamic_cast<CollideableEntity*>(entity))
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			renderMeshes(collideableEntity->getCollisionModel().getMeshes());
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
	}

	m_entityShader.stopProgram();
}

void Renderer::renderMeshes(std::vector<std::unique_ptr<Mesh>>& meshes)
{
	for (auto it = meshes.begin(); it != meshes.end(); ++it)
	{
		Mesh* mesh = it->get();

		// bind appropriate textures
		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < mesh->getTextures().size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
											  // retrieve texture number (the N in diffuse_textureN)
			std::string number;
			Texture* texture = mesh->getTextures().at(i).get();
			std::string name = texture->getTypeAsString();
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++); // transfer unsigned int to stream
			else if (name == "texture_normal")
				number = std::to_string(normalNr++); // transfer unsigned int to stream
			else if (name == "texture_height")
				number = std::to_string(heightNr++); // transfer unsigned int to stream

			m_entityShader.setUniform1i(name + number, i);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, texture->getID());
		}

		// draw mesh
		glBindVertexArray(mesh->getVAO());
		glDrawElements(GL_TRIANGLES, (unsigned int)mesh->getIndices().size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}
