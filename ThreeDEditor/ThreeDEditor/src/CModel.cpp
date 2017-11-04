#pragma once

#include "CModel.h"
#include <stb_image.h>

CModel::CModel()
{

}

CModel::CModel(char* path)
{
	LoadModel(path);
}

void CModel::Draw(CShader shader)
{
	for (unsigned int i = 0; i < vMeshes.size(); i++)
	{
		vMeshes[i].Draw(shader);
	}
}

void CModel::LoadModel(std::string path)
{
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR: ASSIMP: " << importer.GetErrorString() << std::endl;
		return;
	}

	sDirectory = path.substr(0, path.find_last_of('/'));

	ProcessNode(scene->mRootNode, scene);
}

void CModel::ProcessNode(aiNode *node, const aiScene *scene)
{
	// process all the nodes meshes
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
		vMeshes.push_back(ProcessMesh(mesh, scene));
	}

	// do the above for its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

CMesh CModel::ProcessMesh(aiMesh *mesh, const aiScene *scene)
{
	std::vector<CVertex> vertices;
	std::vector<GLuint> indices;
	std::vector<CTexture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		CVertex vertex;
		
		// process vertex position, normal and texture co-ordinates
		glm::vec3 vector;
		
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.v3Position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.v3Normal = vector;

		// TODO: CAN CONTAIN UPTO 8 TEXTURE CO-ORDINATES
		// does the mesh contain texture co ordinates
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.v2TexCoords = vec;
		}

		vertices.push_back(vertex);
	}

	// process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	// process material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<CTexture> diffuseMaps = LoadMaterialTextures(material,
			aiTextureType_DIFFUSE, TYPE_DIFFUSE_SHADER);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		std::vector<CTexture> specularMaps = LoadMaterialTextures(material,
			aiTextureType_SPECULAR, TYPE_SPECULAR_SHADER);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return CMesh(vertices, indices, textures);
}

std::vector<CTexture> CModel::LoadMaterialTextures(aiMaterial *material, aiTextureType type,
	std::string TypeName)
{
	std::vector<CTexture> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
	{
		aiString str;
		material->GetTexture(type, i, &str);
		bool isSkip = false;
 		for (unsigned int j = 0; j < vTexturesLoaded.size(); j++)
		{
			if (std::strcmp(vTexturesLoaded[j].filePath.C_Str(), str.C_Str()) == 0)
			{
				textures.push_back(vTexturesLoaded[j]);
				isSkip = true;
				break;
			}
		}
		if (!isSkip)
		{
			CTexture texture;
			texture.nID = TextureFromFile(str.C_Str(), sDirectory, false);
			texture.sType = TypeName;
			texture.filePath = str;
			textures.push_back(texture);
			vTexturesLoaded.push_back(texture);
		}
	}

	return textures;
}

unsigned int CModel::TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}
