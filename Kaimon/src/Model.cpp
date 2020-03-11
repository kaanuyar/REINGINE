#include "Model.h"

Model::Model(std::string const& path)
{
	loadModel(path);
}

std::vector<std::unique_ptr<Mesh>>& Model::getMeshes()
{
	return m_meshes;
}

void Model::loadModel(std::string const& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
		return;
	}

	m_directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

std::unique_ptr<Mesh> Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	// data to fill
	std::vector<Vertx> vertices;
	std::vector<unsigned int> indices;
	std::vector<std::unique_ptr<Texture>> textures;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertx vertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
						  // positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		// normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);

		vertices.push_back(vertex);
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process materials
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// 1. diffuse maps
	std::vector<std::unique_ptr<Texture>> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, Texture::Type::TEXTURE_DIFFUSE);
	textures.insert(textures.end(), std::make_move_iterator(diffuseMaps.begin()), std::make_move_iterator(diffuseMaps.end()));
	// 2. specular maps
	std::vector<std::unique_ptr<Texture>> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, Texture::Type::TEXTURE_SPECULAR);
	textures.insert(textures.end(), std::make_move_iterator(specularMaps.begin()), std::make_move_iterator(specularMaps.end()));
	// 3. normal maps
	std::vector<std::unique_ptr<Texture>> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, Texture::Type::TEXTURE_NORMAL);
	textures.insert(textures.end(), std::make_move_iterator(normalMaps.begin()), std::make_move_iterator(normalMaps.end()));
	// 4. height maps
	std::vector<std::unique_ptr<Texture>> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, Texture::Type::TEXTURE_HEIGHT);
	textures.insert(textures.end(), std::make_move_iterator(heightMaps.begin()), std::make_move_iterator(heightMaps.end()));

	// return a mesh object created from the extracted mesh data
	return std::make_unique<Mesh>(vertices, indices, std::move(textures));
}

std::vector<std::unique_ptr<Texture>> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, Texture::Type typeName)
{
	std::vector<std::unique_ptr<Texture>> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		std::string filePath = m_directory + '/' + str.C_Str();
		textures.push_back(std::make_unique<Texture>(filePath, typeName));

		/*Texture texture;
		texture.id = TextureFromFile(str.C_Str(), directory);
		texture.type = typeName;
		texture.path = str;
		textures.push_back(texture);*/
	}
	return std::move(textures);
}
