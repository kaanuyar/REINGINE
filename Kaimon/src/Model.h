#pragma once

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>


class Model
{
public:
	Model(std::string const &path, bool gamma = false);
	std::vector<Mesh>& getMeshes();

private:
	/*  Functions   */
	void loadModel(std::string const &path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture*> loadMaterialTextures(aiMaterial *mat, aiTextureType type, Texture::Type typeName);

	std::vector<Texture> m_texturesLoaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<Mesh> m_meshes;
	std::string m_directory;
	bool m_gammaCorrection;
};
