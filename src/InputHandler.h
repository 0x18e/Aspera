#pragma once
#include<unordered_map>
#include<string>
#include<GLFW/glfw3.h>

enum ButtonState {NONE, PRESSED, HELD, RELEASED};
struct InputState{
	std::unordered_map<std::string, ButtonState> events;
};


class InputHandler {
public:	
	InputState m_InputState;
	void Init(GLFWwindow const &window);

	void Update();
	bool IsHeld(std::string event);
	bool IsPressed(std::string event);
	bool IsReleased(std::string event);
	void Exit();
};