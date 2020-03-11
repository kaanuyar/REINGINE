#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "Mesh.h"

class Model
{
public:
	Model(std::string const &path);

	std::vector<std::unique_ptr<Mesh>>& getMeshes();
private:
	void loadModel(std::string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	std::unique_ptr<Mesh> processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<std::unique_ptr<Texture>> loadMaterialTextures(aiMaterial *mat, aiTextureType type, Texture::Type typeName);

	/*  Model Data */
	std::vector<std::unique_ptr<Mesh>> m_meshes;
	std::string m_directory;
};