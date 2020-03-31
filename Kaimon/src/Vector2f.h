#pragma once

class Vector2f
{
public:
	Vector2f() : x(0.0f), y(0.0f) { }
	Vector2f(float x, float y) : x(x), y(y) { }
	//Vector2f(const Vector2f& vec) : x(vec.x), y(vec.y) { }
	void increasePosition(float dx, float dy) { x += dx; y += dy; }
	float x, y;
};