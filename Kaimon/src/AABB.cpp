#include "AABB.h"

#include "MathCalc.h"

AABB::AABB(std::vector<float>& vertices)
{
	calculateBoundingBox(vertices);
}

void AABB::update(Entity& entity)
{
	setWorldMinVertex(MathCalc::transformVector3f(entity, m_localMinVertex));
	setWorldMaxVertex(MathCalc::transformVector3f(entity, m_localMaxVertex));

	//std::cout << "min: " << m_worldMinVertex.x << " " << m_worldMinVertex.y << " " << m_worldMinVertex.z << std::endl;
	//std::cout << "max: " << m_worldMaxVertex.x << " " << m_worldMaxVertex.y << " " << m_worldMaxVertex.z << std::endl;
}

bool AABB::collideWith(ICollider* collider)
{
	return collider->collideWith(this);
}

bool AABB::collideWith(AABB* aabb)
{
	return (m_worldMaxVertex.x > aabb->getWorldMinVertex().x &&
			m_worldMinVertex.x < aabb->getWorldMaxVertex().x &&
			m_worldMaxVertex.y > aabb->getWorldMinVertex().y &&
			m_worldMinVertex.y < aabb->getWorldMaxVertex().y &&
			m_worldMaxVertex.z > aabb->getWorldMinVertex().z &&
			m_worldMinVertex.z < aabb->getWorldMaxVertex().z);
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

