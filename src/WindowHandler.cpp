#include "WindowHandler.h"
#include "GLFW/glfw3.h"


WindowHandler WindowHandler::m_WindowInstance;
void FrameBufferSizeCallback(GLFWwindow* window, int x, int y) {
	glViewport(0, 0, x, y);
}

bool WindowHandler::CreateWindow(int width, int height, std::string name) {
	LOG("Creating Window");
	this->m_pWindow = glfwCreateWindow(width, height,
		name.c_str(),
		nullptr,
		nullptr);
	if (!m_pWindow) {
		LOG("Could not create window");
		return false;
	}

	glfwMakeContextCurrent(this->m_pWindow);
	glfwSetFramebufferSizeCallback(this->m_pWindow, FrameBufferSizeCallback);
	glfwSetWindowSizeLimits(this->m_pWindow, this->m_nWindowWidth,
		this->m_nWindowHeight,
		this->m_nWindowWidth,
		this->m_nWindowHeight
	);

	return true;
}

bool WindowHandler::Init(int width, int height, std::string name) {
	// no need for error checking here this should be managed by whoever is using this
	this->m_nWindowWidth = width;
	this->m_nWindowHeight = height;
	return this->CreateWindow(this->m_nWindowWidth, m_nWindowHeight);
}

bool WindowHandler::ChangeResolution(int x, int y) {
	return false;
}


WindowHandler::~WindowHandler() {
    LOG("Cleaning up window");
	LOG(m_pWindow);
    if (this->m_pWindow != nullptr) {
        glfwDestroyWindow(this->m_pWindow);
		this->m_pWindow = nullptr;
		this->m_Name.clear();
        LOG("Window destroyed");
    }
}
