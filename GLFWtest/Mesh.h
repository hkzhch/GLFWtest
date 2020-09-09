#pragma once
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include <glad/glad.h>

struct Vertex{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
};
struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};



class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	Mesh(std::vector<Vertex> vertices,std::vector<unsigned int> indices,std::vector<Texture> textures);
	void Draw(Shader* shader);
	Mesh(float vertices[]);
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
	

};

