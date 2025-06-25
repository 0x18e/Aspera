#pragma once
#include "tools.h"
#include "Camera.h"
#include ""
class Player {

public:
	Player();
	~Player();
	void Move();
	
private:
	glm::vec3 m_Position;
	glm::vec3 m_Velocity;

	
	float m_fMass;
	Camera m_Camera;
};