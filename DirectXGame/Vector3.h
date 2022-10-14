#pragma once
#include <iostream>
class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3(const Vector3& other);
	~Vector3();
	static Vector3 lerp(const Vector3& start, const Vector3& end, float delta) 
	{
		Vector3 v;
		v.x = start.x * (1.0f - delta) + end.x * (delta);
		v.y = start.y * (1.0f - delta) + end.y * (delta);
		v.z = start.z * (1.0f - delta) + end.z * (delta);
		return v;
	}

public:
	float x, y, z;

	Vector3 operator +(Vector3& other);
	Vector3 operator -(Vector3& other);
	Vector3 operator *(Vector3& other);
};

