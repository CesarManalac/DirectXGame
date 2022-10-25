#include "AGameObject.h"

AGameObject::AGameObject(string name)
{
	this->name = name;
	this->localPos = Vector3D(0, 0, 0);
	this->localScale = Vector3D(1, 1, 1);
	this->localRot = Vector3D(0, 0, 0);
}

AGameObject::~AGameObject()
{
}

void AGameObject::update(float deltaTime)
{
}

void AGameObject::draw(int width, int height)
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPos.x = x;
	this->localPos.y = y;
	this->localPos.z = z;
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPos = pos;
}

Vector3D AGameObject::getLocalPosition()
{
	return this->localPos;
}

string AGameObject::getName()
{
	return this->name;
}

void AGameObject::setScale(float x, float y, float z)
{
	this->localScale.x = x;
	this->localScale.y = y;
	this->localScale.z = z;
}

void AGameObject::setScale(Vector3D scaleValue)
{
	this->localScale = scaleValue;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRot.x = x;
	this->localRot.y = y;
	this->localRot.z = z;
}

void AGameObject::setRotation(Vector3D rotationValue)
{
	this->localRot = rotationValue;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRot;
}

void AGameObject::setView(Matrix4x4 viewMatrix)
{
}
