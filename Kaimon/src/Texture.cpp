#define STB_IMAGE_IMPLEMENTATION
#include <STB/stb_image.h>
#include <iostream>

#include "Texture.h"
#include <GLAD/glad.h>

Texture::Texture(std::string texturePath, Type textureType)
	: m_id{ 0 }, m_path(texturePath), m_type(textureType)
{
	init(texturePath);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::init(std::string& texturePath)
{
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height, nrChannels;
	//stbi_set_flip_vertically_on_load(true);
	
	unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		unsigned int bitDepth;
		if (nrChannels == 3)
			bitDepth = GL_RGB;
		else if (nrChannels == 4)
			bitDepth = GL_RGBA;

		glTexImage2D(GL_TEXTURE_2D, 0, bitDepth, width, height, 0, bitDepth, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

}


unsigned int Texture::getID()
{
	return m_id;
}

std::string Texture::getPath()
{
	return m_path;
}

Texture::Type Texture::getType()
{
	return m_type;
}

std::string Texture::getTypeAsString()
{
	switch (m_type)
	{
		case Texture::Type::TEXTURE_DIFFUSE: return "texture_diffuse";
		case Texture::Type::TEXTURE_SPECULAR: return "texture_specular";
		case Texture::Type::TEXTURE_NORMAL: return "texture_normal";
		case Texture::Type::TEXTURE_HEIGHT: return "texture_height";
		default: return "unknown_type";
	}
}
