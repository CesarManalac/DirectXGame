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
