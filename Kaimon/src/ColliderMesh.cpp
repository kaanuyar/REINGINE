#include "ColliderMesh.h"
#include <glad/glad.h>

ColliderMesh::ColliderMesh(std::vector<Vector3f>&& vertices, std::vector<unsigned int>&& indices)
	: m_vertices(std::move(vertices)), m_indices(std::move(indices))
{
	setupMesh();
}

ColliderMesh::~ColliderMesh()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
}

unsigned int ColliderMesh::getVAO()
{
	return m_VAO;
}

std::vector<Vector3f>& ColliderMesh::getVertices()
{
	return m_vertices;
}

std::vector<unsigned int>& ColliderMesh::getIndices()
{
	return m_indices;
}

void ColliderMesh::setupMesh()
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
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vector3f), &m_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

	// set the vertex attribute pointers
	// vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), (void*)0);

	glBindVertexArray(0);
}
