#pragma once
#include "CShader.h"
#include "CMesh.h"
#include "CTexture.h"

// TODO: Update all name of all the data memebers of the class to preced "m"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//#include "CComponent.h"

class CModel
{
public:
	CModel();
	CModel(char *path);
	void LoadModel(std::string path);
	void Render(CShader* shader);

private:
	std::vector<CMesh> vMeshes;
	std::string sDirectory;
	std::vector<CTexture> vTexturesLoaded;

	void ProcessNode(aiNode *node, const aiScene *scene);
	CMesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<CTexture> LoadMaterialTextures(aiMaterial *material, aiTextureType type,
		std::string TypeName);
	unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
};