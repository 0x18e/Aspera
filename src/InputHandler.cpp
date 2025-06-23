#include "InputHandler.h"


InputHandler InputHandler::m_sInstance;

double InputHandler::m_dPitch = 0.0f;
double InputHandler::m_dYaw = -90.0f;
double InputHandler::lastX = 0.0f;
double InputHandler::lastY = 0.0f;
bool InputHandler::m_bFirstMouse = true;

void InputHandler::MouseCallback(GLFWwindow* window, double xpos, double ypos) {

	if (m_bFirstMouse) {
		lastX = WindowHandler::Get().GetWidth() / 2;
		lastY = WindowHandler::Get().GetHeight() / 2;
		m_bFirstMouse = false;
	}
	float xOffset = xpos - lastX;
	float yOffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.2f;

	xOffset *= sensitivity;
	yOffset *= sensitivity;

	m_dYaw += xOffset;
	m_dPitch += yOffset;
	
	// clamping
	if (m_dPitch > 89.0f)
		m_dPitch = 89.0f;
	if (m_dPitch < -89.0f)
		m_dPitch = -89.0f;

	
}

double InputHandler::GetPitch() {
	return m_dPitch;
}
double InputHandler::GetYaw() {
	return m_dYaw;
}

bool InputHandler::Init(GLFWwindow &window) {
	this->m_pWindow = &window;
	if (!m_pWindow) {
		LOG("Input window pointer is garbage");
		return false;
	}
	return true;
}

void InputHandler::Update() {
	glfwPollEvents();
}

bool InputHandler::IsHeld(int key) {
	int state = glfwGetKey(this->m_pWindow, key);
	if (state == GLFW_PRESS && state != GLFW_RELEASE) {
		// should be held
		return true;
	}
	return false;
}
bool InputHandler::IsPressed(int key) {
	return (glfwGetKey(this->m_pWindow, key) == GLFW_PRESS);
}
bool InputHandler::IsReleased(int key) {
	return (glfwGetKey(this->m_pWindow, key) == GLFW_RELEASE);
}

void InputHandler::Cleanup() {
	if (this->m_pWindow) {
		// Dangling pointers
		m_pWindow = nullptr;
	}
}
InputHandler::InputHandler() {	
	// does nothing
	m_pWindow = nullptr;
}
InputHandler::~InputHandler() {
	LOG("Calling input handlers cleanup");
	this->Cleanup();
}

