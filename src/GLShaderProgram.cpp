#include <iostream>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include "GLShaderProgram.hpp"
#include "helpers.hpp"

GLShaderProgram::GLShaderProgram(GLuint handle) :
	handle_(handle),
	isCompiled_(false)
{

}

void GLShaderProgram::setUniform(GLint location, const GLfloat f)
{
	glUniform1f(location, f);
}

void GLShaderProgram::setUniform(GLint location, const glm::mat4& mat)
{
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
}

void GLShaderProgram::setUniform(const GLchar* name, const GLfloat f)
{
	const auto location = glGetUniformLocation(handle_, name);
	setUniform(location, f);
}

void GLShaderProgram::setUniform(const GLchar* name, const glm::mat4& mat)
{
	const auto location = glGetUniformLocation(handle_, name);
	setUniform(location, mat);
}

void GLShaderProgram::addShaderFromFile(ShaderType type, std::string filePath)
{
	shaders_.emplace_back(type, filePath);
}

bool GLShaderProgram::compileShader(Shader& shader)
{
	GLenum shaderType;
	switch (shader.type_)
	{
	case ShaderType::Fragment:
		shaderType = GL_FRAGMENT_SHADER;
		break;
	case ShaderType::Vertex:
		shaderType = GL_VERTEX_SHADER;
		break;
	}

	shader.handle_ = glCreateShader(shaderType);

	if (shader.isFromFile_)
	{
		auto fileContent = mc::getFileContent(shader.filePath_);
		std::string shaderSource(fileContent.begin(), fileContent.end());

		const GLchar* source = shaderSource.c_str();
		GLint length = shaderSource.size();

		glShaderSource(shader.handle_, 1, &source, &length);
	}

	glCompileShader(shader.handle_);

	GLint success = 0;
	glGetShaderiv(shader.handle_, GL_COMPILE_STATUS, &success);

	if (success)
	{
		shader.isCompiled_ = true;
	}
	else
	{
		GLchar info[512] = {};
		GLsizei length;

		glGetShaderInfoLog(shader.handle_, sizeof(info), &length, info);

		std::cout << info;
	}

	return success == GL_TRUE;
}

bool GLShaderProgram::compile()
{
	bool errorOccured = false;
	
	for (Shader& shader : shaders_)
	{
		if (compileShader(shader))
		{
			std::cout << "Compiled shader " << shader.handle_ << std::endl;
			glAttachShader(handle_, shader.handle_);
		}
		else
		{
			std::cout << "Cannot compile shader" << std::endl;
			errorOccured = true;
			break;
		}
	}

	if (errorOccured)
		std::cout << "Cannot compile shader program" << std::endl;
	else
		glLinkProgram(handle_);

		isCompiled_ = !errorOccured;

	return isCompiled_;
}

void GLShaderProgram::use()
{
	glUseProgram(handle_);
}

Shader::Shader(ShaderType type, std::string filePath) :
	type_(type),
	filePath_(filePath),
	isFromFile_(true),
	isCompiled_(false)
{

}

ShaderType Shader::getType() const
{
	return type_;
}