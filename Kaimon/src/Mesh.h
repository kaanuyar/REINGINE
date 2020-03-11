#pragma once

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

struct Vertx {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
};

class Mesh {
public:
	Mesh(std::vector<Vertx> vertices, std::vector<unsigned int> indices, std::vector<Texture*> textures);
	~Mesh();

	unsigned int getVAO();
	std::vector<Vertx>& getVertices();
	std::vector<unsigned int>& getIndices();
	std::vector<Texture*>& getTextures();
private:
	void setupMesh();
	/*  Render data  */
	unsigned int m_VBO, m_EBO;
	std::vector<Vertx> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<Texture*> m_textures;
	unsigned int m_VAO;
};
