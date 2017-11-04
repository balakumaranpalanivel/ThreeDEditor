#pragma once
// TODO: Update all name of all the data memebers of the class to preced "m"

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#define LENGTH_SHADER_ERROR 512

class CShader
{
public:
	GLuint glnProgramID;

	CShader(const GLchar* vertexPath, const GLchar* fragmentPath);
	
	void Use();

	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;

};
