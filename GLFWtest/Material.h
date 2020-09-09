#pragma once

#include "Shader.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Material
{
public:
	enum Slot
	{
		Diffuse,
		Specular,
		Emission
	};
	Shader* shader;
	glm::vec3 ambient;
	unsigned int emission;
	unsigned int diffuse;
	unsigned int specular;
	float shininess;
	Material(Shader* _shader,glm::vec3 _ambient,unsigned int _diffuse, unsigned int _specular,unsigned int _emission,float _shininess);

};

