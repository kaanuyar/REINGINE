#include "AABB.h"

AABB::AABB(std::vector<float>& vertices)
	: m_minVertex(0.0f, 0.0f, 0.0f), m_maxVertex(0.0f, 0.0f, 0.0f)
{
	calculateBoundingBox(vertices);
}

// assumes vertices array consists of pos(3), texture(2) and normal(3)
void AABB::calculateBoundingBox(std::vector<float>& vertices)
{
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (i % 8 == 0)
		{
			if (i == 0 || vertices[i] < m_minVertex.x)
				m_minVertex.x = vertices[i];
			else if (i == 0 || vertices[i] > m_maxVertex.x)
				m_maxVertex.x = vertices[i];
		}
		else if (i % 8 == 1)
		{
			if (i == 1 || vertices[i] < m_minVertex.y)
				m_minVertex.y = vertices[i];
			else if (i == 1 || vertices[i] > m_maxVertex.y)
				m_maxVertex.y = vertices[i];
		}
		else if (i % 8 == 2)
		{
			if (i == 2 || vertices[i] < m_minVertex.z)
				m_minVertex.z = vertices[i];
			else if (i == 2 || vertices[i] > m_maxVertex.z)
				m_maxVertex.z = vertices[i];
		}
	}
}


Vector3f AABB::getMinVertex()
{
	return m_minVertex;
}

Vector3f AABB::getMaxVertex()
{
	return m_maxVertex;
}

