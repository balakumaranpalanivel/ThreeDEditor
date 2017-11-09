#pragma once
// TODO: Update all name of all the data memebers of the class to preced "m"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "CTransform.h"

class CRenderEngine;

#define LENGTH_SHADER_ERROR 512

class CShader
{
public:
	GLuint glnProgramID;
	CShader();
	CShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	void LoadShaders(const GLchar* vertexPath, const GLchar* fragmentPath);

	void Use();

	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetMat4(const std::string &name, glm::mat4 value) const;

	virtual void UpdateUniforms(const CTransform& transform, CRenderEngine* renderingEngine);

};
