#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float speedX = 0.0f;
	float speedY = 0.0f;
	float speedZ = 0.0f;
	float Yaw;
	float Pitch;
	glm::mat4 getViewMatrix();
	void ProcessMouseMovement(float xoffset, float yoffset);
	void updateCameraPositions();
private:
	void updateCameraVectors();


};