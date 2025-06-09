#pragma once
#include<unordered_map>
#include<string>
#include<GLFW/glfw3.h>
#include "tools.h"



class InputHandler {
private:
	static InputHandler m_sInstance;
	GLFWwindow* m_pWindow;
	InputHandler();
	
public:
	static InputHandler& Get() {
		return m_sInstance;
	}

	bool Init(GLFWwindow *window);

	void Update();
	// Minimal approach to input, later on will add previously held keys, vs current keys, etc.
	bool IsHeld(int key);
	bool IsPressed(int key);
	bool IsReleased(int key);
	void Cleanup();
	~InputHandler();
};