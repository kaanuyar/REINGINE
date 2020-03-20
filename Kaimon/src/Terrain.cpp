#include "Terrain.h"


namespace Terrain
{

	Model createTerrain(unsigned int edgeLength, unsigned int divisionFactor, std::unique_ptr<Texture> texture)
	{
		float texture1f = divisionFactor * 1.0f;
		float texture0f = 0.0f;
		std::vector<float> vertices = { -float(edgeLength), 0.0f,  float(edgeLength), texture0f, texture0f, 0.0f, 1.0f, 0.0f,
			float(edgeLength), 0.0f, -float(edgeLength), texture1f, texture1f, 0.0f, 1.0f, 0.0f,
			-float(edgeLength), 0.0f, -float(edgeLength), texture0f, texture1f, 0.0f, 1.0f, 0.0f,
			float(edgeLength), 0.0f,  float(edgeLength), texture1f, texture0f, 0.0f, 1.0f, 0.0f };

		std::vector<unsigned int> indices = { 0, 1, 2, 0, 3, 1 };

		std::vector<Vertx> vertxVec;
		for (int i = 0; i < 4; i++)
		{
			Vertx vertex;
			vertex.Position = glm::vec3(vertices[i * 8], vertices[i * 8 + 1], vertices[i * 8 + 2]);
			vertex.TexCoords = glm::vec2(vertices[i * 8 + 3], vertices[i * 8 + 4]);
			vertex.Normal = glm::vec3(vertices[i * 8 + 5], vertices[i * 8 + 6], vertices[i * 8 + 7]);
			vertxVec.push_back(vertex);
		}

		std::vector<std::unique_ptr<Texture>> texVec;
		texVec.push_back(std::move(texture));

		std::vector<std::unique_ptr<Mesh>> meshVec;
		meshVec.push_back(std::make_unique<Mesh>(std::move(vertxVec), std::move(indices), std::move(texVec)));

		return Model(std::move(meshVec));
	}
}

