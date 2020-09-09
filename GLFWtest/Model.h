#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Mesh.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "stb_image.h"




class Model
{
public:

	Model(std::string path);
	std::vector<Mesh> meshes;
	std::vector<Texture>textures_loaded;
	std::string directory;
	void Draw(Shader* shader);
private:
	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* materical, aiTextureType type, std::string str);
	unsigned int TextureFromFile(std::string path, std::string directory);
};

