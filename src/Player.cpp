#include "Player.h"



Player::Player() {

	this->Spawn();
}
Player::~Player() {

}
//TODO work on player movement, aceleration, velocity, position gets updated, so does camera position as well.
void Player::Move() {
	
	// as bad as this is i want to keep it at a point where i can just delete it all later.
	if (InputHandler::Get().IsPressed(GLFW_KEY_W)) {
		LOG("moving forward");
		// move forward
		//this->m_CameraPosition += this->m_CameraSpeed * m_CameraFront;
		this->m_Velocity += this->m_Camera.GetSensitivity() * this->m_PlayerCameraState.forward;
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_S)) {
		// move back
		this->m_Velocity -= this->m_Camera.GetSensitivity() * this->m_PlayerCameraState.forward;
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_D)) {
		// move right
		this->m_Velocity += glm::normalize(
			glm::cross(this->m_PlayerCameraState.forward, this->m_Camera.GetUpAxis())) * this->m_Camera.GetSensitivity();
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_A)) {
		// move back
		this->m_Velocity -= glm::normalize(
			glm::cross(this->m_PlayerCameraState.forward, this->m_Camera.GetUpAxis())) * this->m_Camera.GetSensitivity();
	}
	/*
	if (InputHandler::Get().IsPressed(GLFW_KEY_SPACE)) {
		// go up
		this->m_CameraPosition.y += m_CameraSpeed;
	}
	if (InputHandler::Get().IsPressed(GLFW_KEY_LEFT_CONTROL)) {
		// go down
		this->m_CameraPosition.y -= m_CameraSpeed;
	}
	*/
	//this->m_CameraPosition.y = 0.0f;
	
	this->m_Position += m_Velocity * 1.0f / 144.0f;
	
	
}

void Player::Spawn() {
	this->m_fMass = 49.0f;
	this->m_fSpeed = 400;
	this->m_Position = glm::vec3(0.0f, 0.0f, 3.0f);
	this->m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Player::UpdateCamera() {
	// Maybe pass in our change in position as reference to update?
	this->m_Camera.Update(this->BuildCamera());
}

glm::mat4& Player::GetViewMatrix() {
	return this->m_Camera.GetViewMatrix();
}

glm::vec3 Player::GetForwardVector() {

	glm::vec3 direction;
	// Rotation input would be here.
	direction.x = cos(glm::radians(InputHandler::Get().GetYaw())) * cos(glm::radians(InputHandler::Get().GetPitch()));
	direction.y = sin(glm::radians(InputHandler::Get().GetPitch()));
	direction.z = sin(glm::radians(InputHandler::Get().GetYaw())) * cos(glm::radians(InputHandler::Get().GetPitch()));
	return glm::normalize(direction);
}


CameraState Player::BuildCamera() {
	CameraState state;
	state.eyeOffset = glm::vec3(0.0f, 1.5f, 0.0f);
	state.fov = this->m_fFov;
	state.position = this->m_Position; // maybe add eyeOffset to this?
	state.viewPunchAngles = this->m_LocalViewPunch;
	state.forward = this->GetForwardVector();
	this->m_PlayerCameraState = state;
	return this->m_PlayerCameraState;
}
