#include "Camera.h"

Camera::Camera(float fov, float aspectRatio,float near, float far)
{
	m_fov = fov;
	m_near = near;
	m_aspectRatio = aspectRatio;
	m_far = far;
	m_projectionMatrix = glm::perspective(m_fov, m_aspectRatio, m_near, m_far);
}

Camera::~Camera()
{
}

Camera& Camera::move(const Vector3  dv)
{
	m_position.add(dv);
	return *this;
}


//setters
Camera& Camera::setPosition(const Vector3 newPos)
{
	m_position = newPos;
	return *this;
}

Camera & Camera::setForward(const Vector3  newforward)
{
	m_forward = newforward.normalized();
	return *this;
}


//getters
Vector3 Camera::GetPosition() const
{
	return m_position;
}

Vector3 Camera::GetForward() const
{
	return m_forward;
}

glm::mat4 Camera::getModelViewMatrix() const
{
	return glm::lookAt(m_position.toVec3(),
		m_position.Copy().add(m_forward.normalized()).toVec3(), 
		glm::vec3(0, 1, 0));
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return m_projectionMatrix;
}
