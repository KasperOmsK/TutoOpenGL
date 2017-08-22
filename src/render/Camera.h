#pragma once
#include "../math/Vector3.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
private:
	float m_fov;
	float m_near;
	float m_far;
	float m_aspectRatio;
	
	Vector3 m_position;
	Vector3 m_forward;
	Vector3 m_up;

	glm::mat4 m_projectionMatrix;

public:
	Camera(float fov, float aspectRatio ,float near, float far);
	~Camera();

	Camera& move(const Vector3 dv);
	
	//getters

	glm::mat4 getModelViewMatrix() const;
	glm::mat4 getProjectionMatrix() const;
	Vector3 GetPosition() const;
	Vector3 GetForward() const;
	Vector3 GetRight() const;

	//setters
	Camera& setPosition(const Vector3 newPos);
	Camera& setForward(const Vector3 forward);
};

