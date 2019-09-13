#include "RayCaster.h"
#include "MathCalc.h"

RayCaster::RayCaster(Camera& camera, ViewFrustum& frustum)
	: m_camera(camera), m_frustum(frustum)
{
}

Vector3f RayCaster::castRay(float xpos, float ypos)
{
	return MathCalc::createRayCast(m_camera, m_frustum, xpos, ypos);
}

Vector3f RayCaster::findIntersectionPointForXPlane(Vector3f ray)
{
	return MathCalc::findIntersectionPointForXPlane(ray, m_camera);
}
