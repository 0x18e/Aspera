#pragma once
#include<iostream>

#include "glad/glad.h"
#include "WindowHandler.h"
#include "stb_image.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "tools.h"
#include<vector>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "InputHandler.h"




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
