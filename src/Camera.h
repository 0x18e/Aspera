#pragma once



#include<glm/vec3.hpp>
#include<glm/mat3x3.hpp>
#include<glm/ext/matrix_transform.hpp>
#include "InputHandler.h"



class Camera {

public:
	Camera();
	~Camera();
	void SetCameraPosition(const glm::vec3& position);
	void SetCameraVelocity(const glm::vec3& velocity);
	void SetCameraSpeed(const float& speed);
	void MoveCamera(); // Change this later, really bad right now just temporary
	glm::mat4& GetViewMatrix();
	void Update();

private:
	// Camera class
	// A lot of these static variables are actually very stupid, no need to have them as static.
	//glm::vec3 m_CameraVelocity; // only one instance of throughout all classes of type camera
	//static float m_CameraSpeed;
	//static glm::vec3 m_Position; // can use static variables in class functions NOT IN SCOPE
	float m_CameraSpeed;
	glm::vec3 m_CameraVelocity; // Might just need to be changed or removed depending on how i want the camera

	// 3 important variables
	// 1. camera's position
	glm::vec3 m_CameraPosition;
	// 2. the up axis relative to the camera
	glm::vec3 m_UpAxis;
	// 3. the direction vector we want to face, this would be what we're looking at i think.
	glm::vec3 m_CameraFront; // maybe a better name?


	// need a view matrix
	glm::mat4 m_ViewMatrix;

};

