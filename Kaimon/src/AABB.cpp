#include "AABB.h"

#include "MathCalc.h"

AABB::AABB(Entity& entity)
{
	calculateBoundingBox(entity.getModel());
	this->update(entity);
	// add update method here for the creation this shit is stupid is hell and give entity to this function not vertices :)
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
				if (k == 0 || vertices[i].Position.x < m_localMinVertex.x)
					m_localMinVertex.x = vertices[i].Position.x;
				if (k == 0 || vertices[i].Position.x > m_localMaxVertex.x)
					m_localMaxVertex.x = vertices[i].Position.x;
			}
			else if (i % 3 == 1)
			{
				if (k == 1 || vertices[i].Position.y < m_localMinVertex.y)
					m_localMinVertex.y = vertices[i].Position.y;
				if (k == 1 || vertices[i].Position.y > m_localMaxVertex.y)
					m_localMaxVertex.y = vertices[i].Position.y;
			}
			else if (i % 3 == 2)
			{
				if (k == 2 || vertices[i].Position.z < m_localMinVertex.z)
					m_localMinVertex.z = vertices[i].Position.z;
				if (k == 2 || vertices[i].Position.z > m_localMaxVertex.z)
					m_localMaxVertex.z = vertices[i].Position.z;
			}

			k++;
		}
	}
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

