#pragma once

#include <glad/glad.h> // holds all OpenGL type declarations

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>
#include "Texture.h"

struct Vertx 
{
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
};

class Mesh {
public:
	Mesh(std::vector<Vertx> vertices, std::vector<unsigned int> indices, std::vector<std::unique_ptr<Texture>> textures);
	~Mesh();

	unsigned int getVAO();
	std::vector<Vertx>& getVertices();
	std::vector<unsigned int>& getIndices();
	std::vector<std::unique_ptr<Texture>>& getTextures();
private:
	// initializes all the buffer objects/arrays
	void setupMesh();

	/*  Render data  */
	unsigned int m_VAO, m_VBO, m_EBO;
	std::vector<Vertx> m_vertices;
	std::vector<unsigned int> m_indices;
	std::vector<std::unique_ptr<Texture>> m_textures;
};