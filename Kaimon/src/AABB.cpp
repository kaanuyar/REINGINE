#include "AABB.h"

AABB::AABB(std::vector<float>& vertices)
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
			if (i == 0 || vertices[i] < m_localMinVertex.x)
				m_localMinVertex.x = vertices[i];
			if (i == 0 || vertices[i] > m_localMaxVertex.x)
				m_localMaxVertex.x = vertices[i];
		}
		else if (i % 8 == 1)
		{
			if (i == 1 || vertices[i] < m_localMinVertex.y)
				m_localMinVertex.y = vertices[i];
			if (i == 1 || vertices[i] > m_localMaxVertex.y)
				m_localMaxVertex.y = vertices[i];
		}
		else if (i % 8 == 2)
		{
			if (i == 2 || vertices[i] < m_localMinVertex.z)
				m_localMinVertex.z = vertices[i];
			if (i == 2 || vertices[i] > m_localMaxVertex.z)
				m_localMaxVertex.z = vertices[i];
		}
	}

	setWorldMinVertex(m_localMinVertex);
	setWorldMaxVertex(m_localMaxVertex);
}


Vector3f AABB::getLocalMinVertex()
{
	return m_localMinVertex;
}

Vector3f AABB::getLocalMaxVertex()
{
	return m_localMaxVertex;
}

Vector3f AABB::getWorldMinVertex()
{
	return m_worldMinVertex;
}

Vector3f AABB::getWorldMaxVertex()
{
	return m_worldMaxVertex;
}

void AABB::setWorldMinVertex(Vector3f vec)
{
	m_worldMinVertex.setVector(vec);
}

void AABB::setWorldMaxVertex(Vector3f vec)
{
	m_worldMaxVertex.setVector(vec);
}

