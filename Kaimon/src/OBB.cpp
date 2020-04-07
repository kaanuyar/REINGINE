#include "AABB.h"
#include "MathCalc.h"

OBB::OBB(Entity& entity)
{
	calculateBoundingBox(entity.getModel());
	this->update(entity);
}

void OBB::update(Entity& entity)
{
	m_worldMaxVertex = MathCalc::transformVector3fPos(entity, m_localMaxVertex);
	m_worldMinVertex = MathCalc::transformVector3fPos(entity, m_localMinVertex);

	for (int i = 0; i < m_localCornerVertices.size(); i++)
	{
		m_worldCornerVertices[i] = MathCalc::transformVector3fPos(entity, m_localCornerVertices[i]);
	}

	for (int i = 0; i < m_localFaceNormals.size(); i++)
	{
		m_worldFaceNormals[i] = MathCalc::transformVector3fVec(entity, m_localFaceNormals[i]);
	}
}

bool OBB::collideWith(ICollider* collider)
{
	return collider->collideWith(this);
}


bool OBB::collideWith(AABB* aabb)
{
	return false;
}

bool OBB::collideWith(OBB* obb)
{
	std::vector<Vector3f> axisList;

	// first 6 axes are just basis vectors for each OBB
	axisList.push_back(m_worldFaceNormals[0]);
	axisList.push_back(m_worldFaceNormals[1]);
	axisList.push_back(m_worldFaceNormals[2]);
	axisList.push_back(obb->getWorldFaceNormals()[0]);
	axisList.push_back(obb->getWorldFaceNormals()[1]);
	axisList.push_back(obb->getWorldFaceNormals()[2]);

	// 9 axes created by cross products of basis vectors of both OBBs
	for (int i = 0; i < m_worldFaceNormals.size(); i++)
	{
		for (int j = 0; j < obb->getWorldFaceNormals().size(); j++)
			axisList.push_back(MathCalc::crossVector3f(m_worldFaceNormals.at(i), obb->getWorldFaceNormals().at(i)));
	}

	// check collision for each 15 axes
	for (int i = 0; i < axisList.size(); i++)
	{
		bool isIntersect = isIntersectOBB(m_worldCornerVertices, obb->getWorldCornerVertices(), axisList[i]);
		if (!isIntersect)
			return false;
	}

	return true;
}

bool OBB::isIntersectOBB(std::vector<Vector3f>& aWorldCorners, std::vector<Vector3f>& bWorldCorners, Vector3f& axis)
{
	if (axis == Vector3f(0.0f, 0.0f, 0.0f))
		return true;

	float aMin = std::numeric_limits<float>::max();
	float aMax = std::numeric_limits<float>::lowest();
	float bMin = std::numeric_limits<float>::max();
	float bMax = std::numeric_limits<float>::lowest();

	for (int i = 0; i < aWorldCorners.size(); i++)
	{
		float aDist = MathCalc::dotVector3f(aWorldCorners[i], axis);
		aMin = (aDist < aMin) ? aDist : aMin;
		aMax = (aDist > aMax) ? aDist : aMax;
		float bDist = MathCalc::dotVector3f(bWorldCorners[i], axis);
		bMin = (bDist < bMin) ? bDist : bMin;
		bMax = (bDist > bMax) ? bDist : bMax;
	}

	float longSpan = std::max(aMax, bMax) - std::min(aMin, bMin);
	float sumSpan = aMax - aMin + bMax - bMin;

	return longSpan < sumSpan;
}


void OBB::calculateBoundingBox(Model& model)
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

	// initialize world corners here
	m_worldCornerVertices = m_localCornerVertices;

	// initialize local face normals here
	m_localFaceNormals.push_back(Vector3f(1.0f, 0.0f, 0.0f));
	m_localFaceNormals.push_back(Vector3f(0.0f, 1.0f, 0.0f));
	m_localFaceNormals.push_back(Vector3f(0.0f, 0.0f, 1.0f));

	// initialize world face normals here
	m_worldFaceNormals = m_localFaceNormals;

}


Vector3f OBB::getWorldMinVertex()
{
	return m_worldMinVertex;
}

Vector3f OBB::getWorldMaxVertex()
{
	return m_worldMaxVertex;
}

std::vector<Vector3f>& OBB::getWorldCornerVertices()
{
	return m_worldCornerVertices;
}

std::vector<Vector3f>& OBB::getWorldFaceNormals()
{
	return m_worldFaceNormals;
}

std::unique_ptr<ColliderMesh> OBB::createColliderMesh()
{
	std::vector<Vector3f> vertices = m_localCornerVertices;

	std::vector<unsigned int> indices = { 0, 1, 2,	2, 3, 0,  4, 5, 6,  6, 7, 4,
		0, 3, 4,  3, 7, 4,  3, 6, 7,  2, 6, 3,
		2, 1, 5,  6, 2, 5,  0, 4, 5,  5, 1, 0 };

	return std::make_unique<ColliderMesh>(std::move(vertices), std::move(indices));
}


