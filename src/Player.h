#pragma once
#include "tools.h"
#include "Camera.h"

class Player {

public:
	Player();
	~Player();
	void Move();
	void Spawn();
private:
	glm::vec3 m_Position;
	glm::vec3 m_Velocity;
	void UpdateCamera(); // This should update at the end of our move function
	
	
	float m_fSpeed;
	float m_fMass;
	Camera m_Camera;
};