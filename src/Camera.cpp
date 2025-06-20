#include "Camera.h"

//float Camera::m_CameraSpeed = 5.0f; // maybe fast or slow i think depends on dt
//glm::vec3 Camera::m_CameraVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
//


Camera::Camera() {

	// Constructor
	this->m_ViewMatrix = glm::mat4(1.0f);
	this->m_CameraVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	// SELF NOTE:
	// You may be asking, why would the m_position vector have a z component of 3 instead of -3?
	// When the lookat function is used from glm it generates a transform matrix that translates in the opposite
	// direction of m_position. essentially shifting the whole world rather than actually moving the camera

	this->m_CameraSpeed = 5.0f; // will change according to dt
}

glm::mat4& Camera::GetViewMatrix() {
	return this->m_ViewMatrix; // Should return the view matrix as a reference to be modified
}

void Camera::Update() {
	// Handle camera input here
	// Rotation input would be here.
	/*
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	*/
	// first argument is the camera position
	glm::lookAt(this->m_CameraPosition, this->m_CameraPosition + this->m_CameraFront, this->m_UpAxis);
}

Camera::~Camera() {

	// Resetting values, dont think i need to do this but we'll see, pretty sure i dont
	this->m_ViewMatrix = glm::mat4(1.0f);
	this->m_CameraSpeed = 0.0f;
	this->m_CameraVelocity = glm::vec3(0.0f);
	this->m_CameraPosition = glm::vec3(0.0f);
}

void Camera::SetCameraPosition(const glm::vec3& position) {
	this->m_CameraPosition = position;
}

void Camera::SetCameraVelocity(const glm::vec3& velocity) {
	this->m_CameraVelocity = velocity;
}

void Camera::SetCameraSpeed(const float& speed) {
	this->m_CameraSpeed = speed;
}

