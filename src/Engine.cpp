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

	if (!WindowHandler::Get().Init()) {
		LOG("Failed to initialize window");
		return false;
	}

	if (!InputHandler::Get().Init(*WindowHandler::Get().GetWindow())) {
		LOG("Failed to initialize input handler");
		return false;
	}
	
	// Load opengl functions from glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		// GLAD initialization failed
		LOG("Failed to initialize glad functions");
		return false;
	}
	// Certain textures seem to not be happy with this enabled, the base backpack from ogl
	// works fine and it doesnt even complain about it when this is enabled.
	// Any other texture seems to really disagree and it really wants this off in order to work. 
	//stbi_set_flip_vertically_on_load(true);
	
	glEnable(GL_DEPTH_TEST);
#ifdef VSYNC
	glfwSwapInterval(1); // vsync, use in fullscreen if possible
	// glfw uses DwmFlush when vsync is on in windowed mode. Might lead to less than the refresh rate of monitor
#endif //  VSYNC
	
	return true;
}

void Engine::Run() {
	
	// load models
	// -----------
	// A lot of this is debug code, especially the entirety of the model file
	// This section here with shaders is just testing on both windows and linux
#ifdef WIN32

	// Another thing i need to understand, does each object have its own shader?
	// Or is it just that this main model loading shader is to be used for all models
	// and other models that have their own shaders can be used then and there.
	Shader ourShader("W:\\Projects\\repos\\Aspera\\shaders\\model_loading.vs", "W:\\Projects\\repos\\Aspera\\shaders\\model_loading.fs");

	// load models
	// -----------
	Model ourModel("\\models\\Tommy Vercetti.obj");
#endif // WIN64


	glm::vec3 CameraPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	
	// Temp code
	const float radius = 10.0f;
	
	Camera MainCamera;
	while (!glfwWindowShouldClose(WindowHandler::Get().GetWindow())) { // make this look nicer, put it into a function in the handler
		// input first!
		InputHandler::Get().Update();
		
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f); // red

		ourShader.use();
		
		// This is where the view was originally working, this is where the w mov
		
		glm::vec3 CameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);// This would usually be what we're looking at
		// This gives us the direction that the camera is facing, i hate writing comments like these.
		// But im stupid enough to need them.
		glm::vec3 CameraDirection = glm::normalize(CameraPosition - CameraTarget);
		glm::vec3 up = glm::vec3(0, 1.0f, 0.0f);
		glm::vec3 CameraRight = glm::normalize(glm::cross(up, CameraDirection));
		// Gives right axis for camera
		glm::vec3 CameraUp = glm::cross(CameraDirection, CameraRight); // checks out
		

		/* // Usage of glm::lookAt();
		glm::mat4 view;
		view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
		*/
		/* //Debugging view code
		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -6.0f)); // would be the camera's view matrix
		*/
		//float camX = sin(glfwGetTime()) * radius;
		//float camZ = cos(glfwGetTime()) * radius;
		//glm::mat4 view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0, 0, 0), glm::vec3(0, 1.0f, 0));
		MainCamera.MoveCamera();
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (float)WindowHandler::Get().GetWidth() / WindowHandler::Get().GetHeight(), 0.1f, 100.0f);
		ourShader.SetMat4("projection", projection);
		ourShader.SetMat4("view", MainCamera.GetViewMatrix());
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		ourShader.SetMat4("model", model);
		ourModel.Draw(ourShader);
		

		MainCamera.Update();
		glfwSwapBuffers(WindowHandler::Get().GetWindow());
	}
}

void Engine::Exit() {
	// I have no idea what to write here.
	
}
