#include "Camera.h"

Camera::Camera(string name):AGameObject(name)
{
	m_world_cam.setTranslation(Vector3D(0, 0, -2));
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	Matrix4x4 temp;
	Matrix4x4 world_cam;
	world_cam.setIdentity();

	temp.setIdentity();
	temp.setRotationX(this->getLocalRotation().x);
	world_cam *= temp;

	temp.setIdentity();
	temp.setRotationY(this->getLocalRotation().y);
	world_cam *= temp;

	Vector3D new_pos = m_world_cam.getTranslation() + world_cam.getZDirection() * (m_forward * 0.1f);
	new_pos = new_pos + world_cam.getXDirection() * (m_rightward * 0.1f);
	world_cam.setTranslation(new_pos);
	
	m_world_cam = world_cam;
	world_cam.inverse();
	inverse_world = world_cam;
}

void Camera::draw(int width, int height) {

}

void Camera::setView(Matrix4x4 viewMatrix) {

}

void Camera::SetForwardValue(float forward)
{
	m_forward = forward;
}

void Camera::setRightValue(float right)
{
	m_rightward = right;
}

Matrix4x4 Camera::GetCamera()
{
	return inverse_world;
}
