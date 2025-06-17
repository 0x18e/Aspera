#include "Engine.h"

Engine::Engine() {
	this->Initialize();
}

Engine::~Engine() {
	this->Exit();
}

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

	if (!InputHandler::Get().Init(*m_WindowHandler.GetWindow())) {
		return false;
	}
	
	// Load opengl functions from glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		// GLAD initialization failed
		LOG("Failed to initialize glad functions");
		return false;
	}
	//stbi_set_flip_vertically_on_load(true);
	glEnable(GL_DEPTH_TEST);
	return true;
}

void Engine::Run() {
	
	// load models
	// -----------
	// A lot of this is debug code, especially the entirety of the model file
	// This section here with shaders is just testing on both windows and linux
#ifdef WIN32


	Shader ourShader("W:\\Projects\\repos\\Aspera\\shaders\\model_loading.vs", "W:\\Projects\\repos\\Aspera\\shaders\\model_loading.fs");

	// load models
	// -----------
	Model ourModel("W:\\Projects\\repos\\Aspera\\models\\cat22.obj");
#endif // WIN64



	while (!glfwWindowShouldClose(m_WindowHandler.GetWindow())) { // make this look nicer, put it into a function in the handler
		// input first!
		InputHandler::Get().Update();
		
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // red

		ourShader.use();
		
		// This is where the view was originally working, this is where the w mov
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.0f)); // would be the camera's view matrix
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (float)m_WindowHandler.GetWidth() / m_WindowHandler.GetHeight(), 0.1f, 100.0f);
		ourShader.SetMat4("projection", projection);
		ourShader.SetMat4("view", view);
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.SetMat4("model", model);
		ourModel.Draw(ourShader);
		
		glfwSwapBuffers(m_WindowHandler.GetWindow());
	}
}

void Engine::Exit() {
	// I have no idea what to write here.
	
}
