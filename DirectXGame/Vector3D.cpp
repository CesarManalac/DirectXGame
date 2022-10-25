#include "Vector3D.h"

Vector3D::Vector3D()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3D::Vector3D(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3D::Vector3D(const Vector3D& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

Vector3D::~Vector3D()
{
}

Vector3D Vector3D::operator*(float num)
{
	return Vector3D(x * num, y * num, z * num);
}

Vector3D Vector3D::operator+(Vector3D vec)
{
	return Vector3D(x + vec.x, y + vec.y, z + vec.z);
}
