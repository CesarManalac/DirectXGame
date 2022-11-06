#pragma once
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "AGameObject.h"
#include <iostream>

class Camera : public AGameObject
{
public:
	Camera(string name);
	~Camera();
	void UpdateCamera();
	void SetRotationValue(Vector3D rotation);
	void SetForwardValue(float forward);
	void setRightValue(float right);
	void update(float deltaTime) override;
	void draw(int width, int height)override;
	void setView(Matrix4x4 viewMatrix)override;
	Matrix4x4 GetCamera();
	Matrix4x4 GetNotInverse();

private:
	float m_forward = 0.0f;
	float m_rightward = 0.0f;
	Matrix4x4 m_world_cam;
	Matrix4x4 inverse_world;
	Vector3D rotVal = Vector3D(0, 0, 0);
};

