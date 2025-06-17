#pragma once
#include <glad/glad.h> // include glad to get the required OpenGL headers
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {


public:
	// Programs ID
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	// Use this shader program
	void use(void);
	// This is weird...
	void SetBool(const char* name, bool value) const;
	void SetInt(const char* name, int value) const;
	void SetFloat(const char* name, float value) const;
	void SetMat4(const char* name, glm::mat4 matrix);


};

