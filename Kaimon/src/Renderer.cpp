#include "Renderer.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>


void Renderer::renderScene(Camera& camera, ViewFrustum& frustum, Light& light, std::vector<Entity*>& entityList)
{
	prepareRender();
	renderEntities(camera, frustum, light, entityList);
	renderColliders(camera, frustum, light, entityList);
}

void Renderer::prepareRender()
{
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::renderEntities(Camera & camera, ViewFrustum & frustum, Light & light, std::vector<Entity*>& entityList)
{
	m_entityShader.useProgram();

	m_entityShader.loadProjectionMatrix(frustum);
	m_entityShader.loadViewPos(camera);
	m_entityShader.loadViewMatrix(camera);
	m_entityShader.loadLight(light);

	for (Entity* entity : entityList)
	{
		m_entityShader.loadTransformationMatrix(*entity);
		renderMeshes(entity->getModel().getMeshes());
	}

	m_entityShader.stopProgram();
}

void Renderer::renderMeshes(std::vector<std::unique_ptr<Mesh>>& meshes)
{
	for (auto it = meshes.begin(); it != meshes.end(); ++it)
	{
		Mesh* mesh = it->get();

		unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;
		for (unsigned int i = 0; i < mesh->getTextures().size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);

			std::string number;
			Texture* texture = mesh->getTextures().at(i).get();
			std::string name = texture->getTypeAsString();
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);
			else if (name == "texture_normal")
				number = std::to_string(normalNr++);
			else if (name == "texture_height")
				number = std::to_string(heightNr++);

			m_entityShader.setUniform1i(name + number, i);
			glBindTexture(GL_TEXTURE_2D, texture->getID());
		}

		glBindVertexArray(mesh->getVAO());
		glDrawElements(GL_TRIANGLES, (unsigned int)mesh->getIndices().size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}

void Renderer::renderColliders(Camera& camera, ViewFrustum& frustum, Light& light, std::vector<Entity*>& entityList)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m_colliderShader.useProgram();

	m_colliderShader.loadProjectionMatrix(frustum);
	m_colliderShader.loadViewMatrix(camera);

	for (Entity* entity : entityList)
	{
		CollideableEntity* collideableEntity = nullptr;
		if (collideableEntity = dynamic_cast<CollideableEntity*>(entity))
		{
			ColliderMesh* colliderMesh = collideableEntity->getColliderMesh();
			m_colliderShader.loadTransformationMatrix(*entity);
			glBindVertexArray(colliderMesh->getVAO());
			glDrawElements(GL_TRIANGLES, (unsigned int)colliderMesh->getIndices().size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}

	m_colliderShader.stopProgram();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

