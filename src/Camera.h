#pragma once



#include<glm/vec3.hpp>
#include<glm/mat3x3.hpp>

class Camera {
	// Camera class
	static glm::vec3 m_CameraVelocity; // only one instance of throughout all classes of type camera
	static float m_CameraSpeed;
	static glm::vec3 m_Position;
	
	// need a view matrix
	glm::mat4 m_ViewMatrix;
public:
	Camera();
	~Camera();
	void SetCameraPosition(const glm::vec3& position);
	void SetCameraVelocity(const glm::vec3& velocity);
	void SetCameraSpeed(const float& speed);
	glm::mat4& GetViewMatrix();
	void Update();
};

