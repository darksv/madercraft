#include <iostream>

#include "helpers.hpp"
#include "Shader.hpp"

GLuint loadAndCompileShader(GLenum shaderType, std::string shaderSource)
{
	GLuint shader = glCreateShader(shaderType);

	const GLchar * source = shaderSource.c_str();

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}


Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) :
	vertexShaderPath_(vertexShaderPath),
	fragmentShaderPath_(fragmentShaderPath)
{
	auto vertexShaderData = getFileContent(vertexShaderPath_);
	auto fragmentShaderData = getFileContent(fragmentShaderPath_);
	std::string vertexShaderSource(vertexShaderData.begin(), vertexShaderData.end());
	std::string fragmentShaderSource(fragmentShaderData.begin(), fragmentShaderData.end());

	vertexShader_ = loadAndCompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	fragmentShader_ = loadAndCompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

	program_ = glCreateProgram();
	glAttachShader(program_, vertexShader_);
	glAttachShader(program_, fragmentShader_);
	glLinkProgram(program_);

	glDeleteShader(vertexShader_);
	glDeleteShader(fragmentShader_);
}

GLuint Shader::getId()
{
	return program_;
}

GLint Shader::getUniform(const GLchar* name)
{
	return glGetUniformLocation(program_, name);
}

