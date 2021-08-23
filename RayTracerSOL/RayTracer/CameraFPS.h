#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	ELEVATE,
	LOWER
};

class CameraFPS
{
public:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUP;
	glm::vec3 cameraRight;
	glm::vec3 worldUP;

	float yaw;
	float pitch;
	float groundLevel = 0 ;

	float cameraSpeed;
	float mouseSensitivity;

	CameraFPS(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 worldUP = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
	CameraFPS(float posX, float posY, float posZ, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f, float yaw = -90.0f, float pitch = 0.0f);

	glm::mat4 GetViewMatrix();

	void ProcessKeyboard(Camera_Movement direction, float deltaTime);
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

private:
	void UpdateCameraVectors();

};