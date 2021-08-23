#include "CameraFPS.h"

CameraFPS::CameraFPS(glm::vec3 position  , glm::vec3 worldUP, float yaw , float pitch)
	: cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), cameraSpeed(2.5f), mouseSensitivity(0.1f)
{	
	cameraPos = position;
	this->worldUP = worldUP;
	this->yaw = yaw;
	this->pitch = pitch;

	UpdateCameraVectors();
}

CameraFPS::CameraFPS(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw , float pitch )
	: yaw(yaw), pitch(pitch), cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), cameraSpeed(2.5f), mouseSensitivity(0.1f)
{
	cameraPos = glm::vec3(posX, posY, posZ);
	worldUP = glm::vec3(upX, upY, upZ);
	UpdateCameraVectors();
}

glm::mat4 CameraFPS::GetViewMatrix()
{
	return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUP);
}

void CameraFPS::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = cameraSpeed * deltaTime;
	if (direction == FORWARD)
	{
		cameraPos += cameraFront * velocity;
	}
	if (direction == BACKWARD)
	{
		cameraPos -= cameraFront * velocity;
	}
	if (direction == LEFT)
	{
		cameraPos -= cameraRight * velocity;
	}
	if (direction == RIGHT)
	{
		cameraPos += cameraRight * velocity;
	}

	//Elevate // Lower //

	if (direction == ELEVATE)
	{
		cameraPos += cameraUP * velocity;
		groundLevel = cameraPos.y;
	}
	if (direction == LOWER)
	{
		cameraPos -= cameraUP * velocity;
		groundLevel = cameraPos.y;
	}


	cameraPos.y = groundLevel; //So it can't fly
}

void CameraFPS::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= mouseSensitivity;
	yoffset *= mouseSensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (constrainPitch)
	{
		if (pitch > 80.0f)
			pitch = 80.0f;
		if (pitch < -80.0f)
			pitch = -80.0f;
	}
	UpdateCameraVectors();
}

void CameraFPS::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
	// also re-calculate the Right and Up vector
	cameraRight = glm::normalize(glm::cross(cameraFront, worldUP));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	cameraUP = glm::normalize(glm::cross(cameraRight, cameraFront));
}
