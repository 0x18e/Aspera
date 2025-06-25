#include "Player.h"



Player::Player() {
	this->m_fMass = 10.0f;
	this->m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_Position = glm::vec3(0, 0, 3); // our main position
}

//TODO work on player movement, aceleration, velocity, position gets updated, so does camera position as well.
void Player::Move() {
	/*
	// as bad as this is i want to keep it at a point where i can just delete it all later.
	if (InputHandler::Get().IsPressed(GLFW_KEY_W)) {
		// move forward
		//this->m_CameraPosition += this->m_CameraSpeed * m_CameraFront;
		this->m_Velocity += this->m
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
	this->m_CameraPosition.y = 0.0f;


	this->UpdateCamera();
	*/
}

void Player::UpdateCamera() {

	this->m_Camera.Update();
}