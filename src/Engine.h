#pragma once
#include<iostream>
#include "Model.h"
#include "glad/glad.h"
#include "WindowHandler.h"
#include "stb_image.h"
#include "Shader.h"
#include "tools.h"
#include "Camera.h"
#include<vector>
#include "InputHandler.h"
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/*TODO
* REWRITE THE ENTIRE Model.h class, this has a lot of weird code copied from opengl
* Use relative paths instead of just hardcoding them.
* fix the whole thing with having the TextureFromFile function be defined in multiple translation units
* 
*/


class Engine {

	// Main functions will be here
	// Initializing all subsystems
	// Run entire simulation, will also include update and frame independent rendering
	// Exit and cleanup everything USING THE RESOURCE MANAGER

private:
	WindowHandler m_WindowHandler;
	

public:
	Engine();
	~Engine();
	bool Initialize();
	void Run();
	void Exit();
};
