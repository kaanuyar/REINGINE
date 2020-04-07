#pragma once
#include "Vector3f.h"
#include <vector>

class ColliderMesh
{
public:
	ColliderMesh(std::vector<Vector3f>&& vertices, std::vector<unsigned int>&& indices);
	~ColliderMesh();

	unsigned int getVAO();
	std::vector<Vector3f>& getVertices();
	std::vector<unsigned int>& getIndices();
private:
	void setupMesh();

	unsigned int m_VAO, m_VBO, m_EBO;

	std::vector<Vector3f> m_vertices;
	std::vector<unsigned int> m_indices;
};