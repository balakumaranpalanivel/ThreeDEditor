#pragma once
// TODO: Update all name of all the data memebers of the class to preced "m"
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "CVertex.h"
#include "CTexture.h"
#include "CShader.h"

class CMesh
{
public:
	// Mesh Data
	std::vector<CVertex>		vVertices;
	std::vector<GLuint>			vIndices;
	std::vector<CTexture>		vTextures;

	CMesh(std::vector<CVertex> vertices,
			std::vector<GLuint> indices,
			std::vector<CTexture> textures);

	void Draw(CShader* shader);

	~CMesh();

private:

	// Rendering Data
	GLuint glnVAO;
	GLuint glnVBO;
	GLuint glnEBO;

	void SetupMesh();

};

