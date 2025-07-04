#pragma once
#include "GLFW/glfw3.h"
#include "tools.h"


// This class follows RAII

class WindowHandler {

public:
	bool Init(int width = 1280, int height = 800, std::string name = "Lorem Ipsum");
	static WindowHandler& Get() {
		return m_WindowInstance;
	}
	int GetWidth() const { return m_nWindowWidth; }
	int GetHeight() const { return m_nWindowHeight; }
	bool ChangeResolution(int x, int y);  // opengl function needed to change resolutions, just wrapped here.
	std::string GetName() { return m_Name; }
	GLFWwindow* GetWindow() { return m_pWindow; }
	void ShowCursor(bool show);
	bool CursorStatus();


	~WindowHandler();


private:

	bool m_bShowCursor;
	static WindowHandler m_WindowInstance;
	WindowHandler() : m_nWindowHeight(800), m_nWindowWidth(1280), m_pWindow(nullptr), m_bShowCursor(true) {
		
	}

	GLFWwindow* m_pWindow;
	int m_nWindowWidth;
	int m_nWindowHeight;
	std::string m_Name;
	
	bool CreateWindow(int width, int height, std::string name="Lorem Ipsum");
};

void FrameBufferSizeCallback(GLFWwindow* window, int x, int y);