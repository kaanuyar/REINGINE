#pragma once
#include <vector>
#include "Vector3f.h"

class AABB 
{
public:
	AABB(std::vector<float>& vertices);
	Vector3f getMinVertex();
	Vector3f getMaxVertex();

private:
	void calculateBoundingBox(std::vector<float>& vertices);

	Vector3f m_minVertex;
	Vector3f m_maxVertex;
};