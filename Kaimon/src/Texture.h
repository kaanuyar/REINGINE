#pragma once
#include <string>

class Texture
{
public:
	enum Type : int
	{
		TEXTURE_DIFFUSE = 0,
		TEXTURE_NORMAL,
		TEXTURE_SPECULAR,
		TEXTURE_HEIGHT
	};

	Texture(std::string texturePath, Type textureType);
	~Texture();
	unsigned int getID();
	std::string getPath();
	Type getType();
	std::string getTypeAsString();

private:
	void init(std::string& texturePath);
	unsigned int m_id;
	Type m_type;
	std::string m_path;
};