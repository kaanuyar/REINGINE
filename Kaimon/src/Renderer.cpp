#include "Renderer.h"
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>

void Renderer::renderEntities(EntityShaderProgram& entityShaderProgram, Camera& camera, ViewFrustum& frustum, std::vector<Entity*>& entityList)
{
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	entityShaderProgram.useProgram();

	entityShaderProgram.loadProjectionMatrix(frustum);
	entityShaderProgram.loadViewPos(camera);
	entityShaderProgram.loadViewMatrix(camera);

	for (Entity* entity : entityList)
	{
		entityShaderProgram.loadTransformationMatrix(*entity);

		std::vector<std::unique_ptr<Mesh>>& vec = entity->getModel().getMeshes();
		for (auto it = vec.begin(); it != vec.end(); ++it)
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

														 // now set the sampler to the correct texture unit
				entityShaderProgram.setUniform1i(name + number, i);
				// and finally bind the texture
				glBindTexture(GL_TEXTURE_2D, texture->getID());
			}

			// draw mesh
			glBindVertexArray(mesh->getVAO());
			glDrawElements(GL_TRIANGLES, (unsigned int) mesh->getIndices().size(), GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
	}
	entityShaderProgram.stopProgram();
}


//std::unordered_map<RawEntity*, std::vector<Entity*>> Renderer::processEntity(std::vector<Entity*>& entityList)
//{
//	std::unordered_map<RawEntity*, std::vector<Entity*>> umap;
//
//	for (Entity* entity : entityList)
//	{
//		RawEntity& rawEntity = entity->getRawEntity();
//
//		if (umap.find(&rawEntity) == umap.end())
//			umap[&rawEntity] = { entity };
//		else
//			umap[&rawEntity].push_back(entity);
//	}
//
//	return umap;
//}

