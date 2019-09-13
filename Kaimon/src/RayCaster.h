#pragma once
#include "Camera.h"
#include "ViewFrustum.h"
#include "EventHandler.h"
#include "Vector3f.h"
#include "IUpdatable.h"

class RayCaster
{
public:
	RayCaster(Camera& camera, ViewFrustum& frustum);

	Vector3f castRay(float xpos, float ypos);
	Vector3f findIntersectionPointForXPlane(Vector3f ray);

private:
	Camera& m_camera;
	ViewFrustum& m_frustum;
};
