#include "CShader.h"

CShader::CShader()
{

}

CShader::CShader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	LoadShaders(vertexPath, fragmentPath);
}

void CShader::LoadShaders(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	// Read the shader code from the source files
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open the files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		// read file contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handles
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR: SHADER : FILE_READ_FAIL." << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// compile shader
	unsigned int vertex, fragment;
	int success;
	char infoLog[LENGTH_SHADER_ERROR];

	// vertex shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// print compile error
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, LENGTH_SHADER_ERROR, NULL, infoLog);
		std::cout << "ERROR: VERTEX_SHADER : FAIL_COMPILATION : " << infoLog << std::endl;
	}

	// fragment shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile error
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, LENGTH_SHADER_ERROR, NULL, infoLog);
		std::cout << "ERROR: FRAGMENT_SHADER : FAIL_COMPILATION : " << infoLog << std::endl;
	}

	// build shader program
	this->glnProgramID = glCreateProgram();
	glAttachShader(this->glnProgramID, vertex);
	glAttachShader(this->glnProgramID, fragment);
	glLinkProgram(this->glnProgramID);
	// print linking error
	glGetProgramiv(this->glnProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->glnProgramID, LENGTH_SHADER_ERROR, NULL, infoLog);
		std::cout<<"ERROR: SHADER_PROGRAM : FAIL_LINKING : " << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void CShader::Use()
{	
	glUseProgram(glnProgramID);
}

void CShader::SetBool(const std::string &name, bool value) const
{
	glUniform1i(
		glGetUniformLocation(glnProgramID, name.c_str()),
		(int)value
	);
}

void CShader::SetInt(const std::string &name, int value) const
{
	glUniform1i(
		glGetUniformLocation(glnProgramID, name.c_str()),
		value
	);
}

void CShader::SetFloat(const std::string &name, float value) const
{
	glUniform1f(
		glGetUniformLocation(glnProgramID, name.c_str()),
		value
	);
}

void CShader::SetMat4(const std::string &name, glm::mat4 value) const
{
	glUniformMatrix4fv(
		glGetUniformLocation(glnProgramID, name.c_str()),
		1,
		GL_FALSE,
		glm::value_ptr(value));
}

void CShader::SetVec3(const std::string &name, glm::vec3 value) const
{
	glUniform3fv(
		glGetUniformLocation(glnProgramID, name.c_str()),
		1,
		glm::value_ptr(value));
}