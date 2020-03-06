#pragma once

class Vector3f
{
public:
	Vector3f() : x(0.0f), y(0.0f), z(0.0f) { }
	Vector3f(float x, float y, float z) : x(x), y(y), z(z) { }
	Vector3f(const Vector3f& vec) : x(vec.x), y(vec.y), z(vec.z) { }
	void setVector(const Vector3f& vec) { x = vec.x;	y = vec.y;	  z = vec.z; }
	void increasePosition(float dx, float dy, float dz) { x += dx; y += dy; z += dz; }
	float x, y, z;

	Vector3f operator-(const Vector3f& vec)
	{
		return Vector3f(this->x - vec.x, this->y - vec.y, this->z - vec.z);
	}

	bool operator==(const Vector3f& vec)
	{
		if (this->x == vec.x && this->y == vec.y && this->z == vec.z)
			return true;
		else
			return false;
	}

	// add substraction and addition method ex: vector3f + vector3f
};