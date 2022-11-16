#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"


using namespace std;
#include "Prerequisites.h";

class AGameObject
{
public:
	AGameObject(string name);
	~AGameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height);

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getLocalPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scaleValue);
	Vector3D getLocalScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rotationValue);
	Vector3D getLocalRotation();

	virtual void setView(Matrix4x4 viewMatrix);

	string getName();
public:
	struct vertex
	{
		Vector3D position;
		Vector3D color;
		Vector3D color1;
	};

	__declspec(align(16))
		struct constant
	{
		Matrix4x4 m_world;
		Matrix4x4 m_view;
		Matrix4x4 m_projection;
		float m_time;
	};

private:
	string name;
	Vector3D localPos;
	Vector3D localScale;
	Vector3D localRot;
	Matrix4x4 localMatrix;
};

