#pragma once
class Vector3
{
public:
	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3(const Vector3& other);
	~Vector3();
	//static Vector3 lerp()

public:
	float x, y, z;

	Vector3 operator +(Vector3& other);
	Vector3 operator -(Vector3& other);
	Vector3 operator *(Vector3& other);
};

