#pragma once
#include <iostream>
class Vector3D
{
public:
	Vector3D();
	Vector3D(float _x, float _y, float _z);
	Vector3D(const Vector3D& other);
	~Vector3D();
	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta) 
	{
		Vector3D v;
		v.x = start.x * (1.0f - delta) + end.x * (delta);
		v.y = start.y * (1.0f - delta) + end.y * (delta);
		v.z = start.z * (1.0f - delta) + end.z * (delta);
		return v;
	}

public:
	float x, y, z;
};

