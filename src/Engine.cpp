#include "Engine.h"

bool Engine::Initialize() {

	if (!glfwInit()) {
		LOG("Could not init glfw");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);


	// Do window stuff here

	if (!this->m_WindowHandler.Init()) {
		return false;
	}
	
	// Load opengl functions from glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		// GLAD initialization failed
		LOG("Failed to initialize glad functions");
		return false;
	}

	return true;
}

void Engine::Run() {
	while (!glfwWindowShouldClose(m_WindowHandler.GetWindow())) { // make this look nicer, put it into a function in the handler

		//processInput(m_WindowHandler.GetWindow()); // use the input handler here to poll
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // red

		


		glfwPollEvents();
		glfwSwapBuffers(m_WindowHandler.GetWindow());
	}
}
