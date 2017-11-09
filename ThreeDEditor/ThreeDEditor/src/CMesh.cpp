#include "CMesh.h"

#include <sstream>


CMesh::CMesh(std::vector<CVertex> vertices,
	std::vector<GLuint> indices, std::vector<CTexture> textures)
{
	this->vVertices = vertices;
	this->vIndices = indices;
	this->vTextures = textures;

	SetupMesh();
}


CMesh::~CMesh()
{
}

void CMesh::SetupMesh()
{
	// Generate VAO, VBO and EBO
	glGenVertexArrays(1, &glnVAO);
	glGenBuffers(1, &glnVBO);
	glGenBuffers(1, &glnEBO);

	glBindVertexArray(glnVAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, glnVBO);
	/*
	If you have a std::vector<T> v, you may obtain a T* pointing to the 
	start of the contiguous data (which is what OpenGL is after) with the expression &v[0].
	*/
	glBufferData(GL_ARRAY_BUFFER, vVertices.size() * sizeof(CVertex), &vVertices[0],
		GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glnEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vIndices.size() * sizeof(GLuint), &vIndices[0],
		GL_STATIC_DRAW);

	// vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, LENGTH_POSITION, GL_FLOAT, GL_FALSE, sizeof(CVertex), (void*)0);

	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, LENGTH_NORMALS, GL_FLOAT, GL_FALSE, sizeof(CVertex),
		(void*)offsetof(CVertex, v3Normal));

	// vertex texture coordinates
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, LENGTH_TEXTURE_COORDINATES, GL_FLOAT, GL_FALSE, sizeof(CVertex),
		(void*)offsetof(CVertex, v2TexCoords));

	glBindVertexArray(0);
}

void CMesh::Draw(CShader* shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

	for (unsigned int i = 0; i < vTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		std::stringstream ss;
		std::string number;
		std::string name = vTextures[i].sType;

		if (TYPE_DIFFUSE_SHADER == name)
		{
			ss << diffuseNr++;
		}
		else if (TYPE_SPECULAR_SHADER == name)
		{
			ss << specularNr++;
		}

		number = ss.str();

		shader->SetFloat(("material." + name + number).c_str(), i);
		glBindTexture(GL_TEXTURE_2D, vTextures[i].nID);
	}

	glActiveTexture(GL_TEXTURE0);

	// draw the mesh
	glBindVertexArray(glnVAO);
	glDrawElements(GL_TRIANGLES, vIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
