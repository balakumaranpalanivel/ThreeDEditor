#pragma once
// TODO: Update all name of all the data memebers of the class to preced "m"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "CShader.h"
#include "CMesh.h"
#include "CTexture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class CModel
{
public:
	CModel(char *path);
	void Draw(CShader shader);

private:
	std::vector<CMesh> vMeshes;
	std::string sDirectory;
	std::vector<CTexture> vTexturesLoaded;

	void LoadModel(std::string path);
	void ProcessNode(aiNode *node, const aiScene *scene);
	CMesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<CTexture> LoadMaterialTextures(aiMaterial *material, aiTextureType type,
		std::string TypeName);
	unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
};