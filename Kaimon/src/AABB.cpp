#include "AABB.h"

#include "MathCalc.h"

AABB::AABB(Entity& entity)
{
	calculateBoundingBox(entity.getModel());
	this->update(entity);
}

void AABB::update(Entity& entity)
{
	m_worldMaxVertex = MathCalc::transformVector3fPos(entity, m_localMaxVertex);
	m_worldMinVertex = MathCalc::transformVector3fPos(entity, m_localMinVertex);
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

bool AABB::collideWith(OBB* obb)
{
	return false;
}


void AABB::calculateBoundingBox(Model& model)
{
	std::vector<std::unique_ptr<Mesh>>& vec = model.getMeshes();
	int k = 0;
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		Mesh* mesh = it->get();
		std::vector<Vertx>& vertices = mesh->getVertices();

		for (unsigned int i = 0; i < vertices.size(); i++)
		{
			if (i % 3 == 0)
			{
				if (k == 0 || vertices[i].position.x < m_localMinVertex.x)
					m_localMinVertex.x = vertices[i].position.x;
				if (k == 0 || vertices[i].position.x > m_localMaxVertex.x)
					m_localMaxVertex.x = vertices[i].position.x;
			}
			else if (i % 3 == 1)
			{
				if (k == 1 || vertices[i].position.y < m_localMinVertex.y)
					m_localMinVertex.y = vertices[i].position.y;
				if (k == 1 || vertices[i].position.y > m_localMaxVertex.y)
					m_localMaxVertex.y = vertices[i].position.y;
			}
			else if (i % 3 == 2)
			{
				if (k == 2 || vertices[i].position.z < m_localMinVertex.z)
					m_localMinVertex.z = vertices[i].position.z;
				if (k == 2 || vertices[i].position.z > m_localMaxVertex.z)
					m_localMaxVertex.z = vertices[i].position.z;
			}

			k++;
		}
	}


	m_worldMaxVertex = m_localMaxVertex;
	m_worldMinVertex = m_localMinVertex;

	// Top square: Counter clock wise starting from top right edge
	m_localCornerVertices.push_back(Vector3f(m_localMaxVertex.x, m_localMaxVertex.y, m_localMaxVertex.z));
	m_localCornerVertices.push_back(Vector3f(m_localMinVertex.x, m_localMaxVertex.y, m_localMaxVertex.z));
	m_localCornerVertices.push_back(Vector3f(m_localMinVertex.x, m_localMaxVertex.y, m_localMinVertex.z));
	m_localCornerVertices.push_back(Vector3f(m_localMaxVertex.x, m_localMaxVertex.y, m_localMinVertex.z));

	// Bottom square: Counter clock wise starting from top right edge
	m_localCornerVertices.push_back(Vector3f(m_localMaxVertex.x, m_localMinVertex.y, m_localMaxVertex.z));
	m_localCornerVertices.push_back(Vector3f(m_localMinVertex.x, m_localMinVertex.y, m_localMaxVertex.z));
	m_localCornerVertices.push_back(Vector3f(m_localMinVertex.x, m_localMinVertex.y, m_localMinVertex.z));
	m_localCornerVertices.push_back(Vector3f(m_localMaxVertex.x, m_localMinVertex.y, m_localMinVertex.z));

}

Vector3f AABB::getWorldMinVertex()
{
	return m_worldMinVertex;
}

Vector3f AABB::getWorldMaxVertex()
{
	return m_worldMaxVertex;
}

std::unique_ptr<ColliderMesh> AABB::createColliderMesh()
{
	std::vector<Vector3f> vertices = m_localCornerVertices;

	std::vector<unsigned int> indices = { 0, 1, 2,	2, 3, 0,  4, 5, 6,  6, 7, 4,
		0, 3, 4,  3, 7, 4,  3, 6, 7,  2, 6, 3,
		2, 1, 5,  6, 2, 5,  0, 4, 5,  5, 1, 0 };

	return std::make_unique<ColliderMesh>(std::move(vertices), std::move(indices));
}


