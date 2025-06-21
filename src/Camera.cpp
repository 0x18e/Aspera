#include "Camera.h"

//float Camera::m_CameraSpeed = 5.0f; // maybe fast or slow i think depends on dt
//glm::vec3 Camera::m_CameraVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
//


Camera::Camera() {

	// Constructor
	this->m_ViewMatrix = glm::mat4(1.0f);
	this->m_CameraVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	// SELF NOTE: will be removed later on
	// You may be asking, why would the m_position vector have a z component of 3 instead of -3?
	// When the lookat function is used from glm it generates a transform matrix that translates in the opposite
	// direction of m_position. essentially shifting the whole world rather than actually moving the camera
	this->m_CameraSpeed = 0.05f; // will change according to dt

	
	this->m_UpAxis = glm::vec3(0.0f, 1.0f, 0.0f);

	// -1 for now cause we dont rotate, our front will always be front
	this->m_CameraFront = glm::vec3(0.0f, 0.0f, -1.0f);

}

glm::mat4& Camera::GetViewMatrix() {
	return this->m_ViewMatrix; // Should return the view matrix as a reference to be modified
}

void Camera::Update() {

	
	// Handle camera input here
	// This might change
	if (InputHandler::Get().IsPressed(GLFW_KEY_ESCAPE)) {
		WindowHandler::Get().ShowCursor(true);
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_F1)) {
		WindowHandler::Get().ShowCursor(false);
	}
	
	// Rotation input would be here.
	/*
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	*/
	// first argument is the camera position
	this->m_ViewMatrix = glm::lookAt(this->m_CameraPosition, this->m_CameraPosition + this->m_CameraFront, this->m_UpAxis);
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

void Camera::MoveCamera() {
	// as bad as this is i want to keep it at a point where i can just delete it all later.
	if (InputHandler::Get().IsPressed(GLFW_KEY_W)) {
		// move forward
		this->m_CameraPosition += this->m_CameraSpeed * m_CameraFront;
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_S)) {
		// move back
		this->m_CameraPosition -= this->m_CameraSpeed * m_CameraFront;
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_D)) {
		// move right
		this->m_CameraPosition += glm::normalize(glm::cross(this->m_CameraFront, this->m_UpAxis)) * m_CameraSpeed;
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_A)) {
		// move back
		this->m_CameraPosition -= glm::normalize(glm::cross(this->m_CameraFront, this->m_UpAxis)) * m_CameraSpeed;
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_SPACE)) {
		// go up
		this->m_CameraPosition.y += m_CameraSpeed;
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_LEFT_CONTROL)) {
		// go down
		this->m_CameraPosition.y -= m_CameraSpeed;
	}
}

