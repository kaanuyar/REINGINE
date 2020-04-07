#pragma once

#include <glad/glad.h> // holds all OpenGL type declarations

#include <string>
#include <vector>
#include <memory>
#include "Texture.h"
#include "Vector3f.h"
#include "Vector2f.h"

struct Vertx
{
	Vector3f position;
	Vector2f texCoords;
	Vector3f normal;
};


class Mesh {
public:
	Mesh(std::vector<Vertx>&& vertices, std::vector<unsigned int>&& indices, std::vector<std::unique_ptr<Texture>>&& textures);
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