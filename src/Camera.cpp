#include "Camera.h"

float Camera::m_CameraSpeed = 5.0f; // maybe fast or slow i think depends on dt
glm::vec3 Camera::m_CameraVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Camera::m_Position;

Camera::Camera() {
	this->m_ViewMatrix = glm::mat4(1.0f);
}

glm::mat4& Camera::GetViewMatrix() {
	return this->m_ViewMatrix; // Should return the view matrix as a reference to be modified
}

Camera::~Camera() {

	// Resetting values, dont think i need to do this but we'll see, pretty sure i dont
	this->m_ViewMatrix = glm::mat4(1.0f);
	this->m_CameraSpeed = 0.0f;
	this->m_CameraVelocity = glm::vec3(0.0f);
	this->m_Position = glm::vec3(0.0f);
}

void Camera::SetCameraPosition(const glm::vec3& position) {
	this->m_Position = position;
}

void Camera::SetCameraVelocity(const glm::vec3& velocity) {
	this->m_CameraVelocity = velocity;
}

void Camera::SetCameraSpeed(const float& speed) {
	this->m_CameraSpeed = speed;
}

