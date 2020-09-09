#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

class LightPoint
{
public:
	glm::vec3 position;
	glm::vec3 angles;
	glm::vec3 color;
	float constant = 1.0f;
	float linear = 0.09;
	float quadratic = 0.032;
	LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
};

