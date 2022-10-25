#pragma once
#include "Matrix4x4.h"
#include "Vector3D.h"
#include <iostream>

class Camera
{
public:
	Camera();
	~Camera();
	void Update();
	void SetRotationValue(Vector3D rotation);
	void SetForwardValue(float forward);
	void setRightValue(float right);
	Matrix4x4 GetCamera();

private:
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	Matrix4x4 m_world_cam;
	Matrix4x4 inverse_world;
	Vector3D rotVal = Vector3D(0, 0, 0);
};

