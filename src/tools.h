#pragma once
#include "glm/ext/matrix_float4x4.hpp"
#include<iostream>

//define debug macro
#define DEBUG 0
#ifdef DEBUG
#define LOG(x) std::cout << x << '\n'
#else
#define LOG(x)
#endif

// should be the base error object when something fails to load
class CPurpleError {

    glm::mat4 model; // base errors model matrix



};

