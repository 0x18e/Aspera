#include "InputHandler.h"


InputHandler InputHandler::m_sInstance;

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
