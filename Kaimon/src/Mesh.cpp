#include "Mesh.h"

Mesh::Mesh(std::vector<Vertx>&& vertices, std::vector<unsigned int>&& indices, std::vector<std::unique_ptr<Texture>>&& textures)
	: m_vertices(vertices), m_indices(indices), m_textures(std::move(textures))
{
	setupMesh();
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

unsigned int Mesh::getVAO()
{
	return m_VAO;
}

std::vector<Vertx>& Mesh::getVertices()
{
	return m_vertices;
}

std::vector<unsigned int>& Mesh::getIndices()
{
	return m_indices;
}

std::vector<std::unique_ptr<Texture>>& Mesh::getTextures()
{
	return m_textures;
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	glBindVertexArray(m_VAO);
	// load data into vertex buffers
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	// A great thing about structs is that their memory layout is sequential for all its items.
	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
	// again translates to 3/2 floats which translates to a byte array.
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertx), &m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertx), (void*)0);
	// vertex texture coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertx), (void*)offsetof(Vertx, texCoords));
	// vertex normals
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertx), (void*)offsetof(Vertx, normal));


	glBindVertexArray(0);
}
