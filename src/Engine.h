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
	//WindowHandler m_WindowHandler; // Now a singleton so this is no longer needed
	
	float dt; // Handling delta time, about time I added this

public:
	Engine();
	~Engine();
	bool Initialize();
	void Run();
	void Exit();
};
