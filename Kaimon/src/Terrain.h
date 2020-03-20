#pragma once
#include "Model.h"
#include "Vector3f.h"

namespace Terrain
{
	Model createTerrain(unsigned int edgeLength, unsigned int divisionFactor, std::unique_ptr<Texture> texture);
};