#pragma once
#include "Model.h"
#include "Vector3f.h"

namespace Terrain
{
	// Constants
	const Vector3f MAX_BOUNDARY_VEC { -5.0f, 0.0f, -5.0f };
	const Vector3f MIN_BOUNDARY_VEC { 5.0f, 0.0f, 5.0f };

	Model createTerrain(unsigned int edgeLength, unsigned int divisionFactor, std::unique_ptr<Texture> texture);
};