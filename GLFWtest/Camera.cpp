#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	WorldUp = worldup;
	Forward = glm::normalize(target - position);
	Right = glm::normalize(glm::cross(Forward, worldup));
	Up = glm::normalize(glm::cross(Forward, Right));
}

Camera:: Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Pitch = pitch;
	Yaw = yaw;
	Position = position;
	WorldUp = worldup;
	Forward.x = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw));
	Forward.y = glm::sin(glm::radians(Pitch));
	Forward.z = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw));
	glm::normalize(Forward);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right,Forward));
}

glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(Position, Position + Forward, WorldUp);
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset)
{
    xoffset *= 0.1f;
    yoffset *= 0.1f;

    Yaw += xoffset;
    Pitch += yoffset;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}



void Camera::updateCameraVectors()
{
	Forward.x = glm::cos(glm::radians(Pitch)) * glm::cos(glm::radians(Yaw));
	Forward.y = glm::sin(glm::radians(Pitch));
	Forward.z = glm::cos(glm::radians(Pitch)) * glm::sin(glm::radians(Yaw));
	glm::normalize(Forward);
	Right = glm::normalize(glm::cross(Forward, WorldUp));
	Up = glm::normalize(glm::cross(Right, Forward));
}
void Camera::updateCameraPositions()
{
	Position += Forward * speedZ * 0.01f + Right * speedX * 0.01f + Up * speedY * 0.01f;
}