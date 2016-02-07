#include <iostream>

#include "helpers.hpp"
#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram() :
	isCompiled_(false)
{

}

GLuint ShaderProgram::getId()
{
	return programId_;
}

GLint ShaderProgram::getUniform(const GLchar* name)
{
	return glGetUniformLocation(programId_, name);
}

void ShaderProgram::addShaderFromFile(ShaderType type, std::string filePath)
{
	shaders_.emplace_back(type, filePath);
}

bool ShaderProgram::compileShader(Shader& shader)
{
	GLenum shaderType;
	switch (shader.type_)
	{
	case ShaderType::FRAGMENT_SHADER:
		shaderType = GL_FRAGMENT_SHADER;
		break;
	case ShaderType::VERTEX_SHADER:
		shaderType = GL_VERTEX_SHADER;
		break;
	}

	shader.shaderId_ = glCreateShader(shaderType);

	if (shader.isFromFile_)
	{
		auto fileContent = getFileContent(shader.filePath_);
		std::string shaderSource(fileContent.begin(), fileContent.end());

		const GLchar* source = shaderSource.c_str();
		GLint length = shaderSource.size();

		glShaderSource(shader.shaderId_, 1, &source, &length);
	}

	glCompileShader(shader.shaderId_);

	GLint success = 0;
	glGetShaderiv(shader.shaderId_, GL_COMPILE_STATUS, &success);

	if (success)
		shader.isCompiled_ = true;

	return success == GL_TRUE;
}

bool ShaderProgram::compile()
{
	if (!isCompiled_)
	{
		bool errorOccured = false;

		programId_ = glCreateProgram();

		for (Shader& shader : shaders_)
		{
			if (compileShader(shader))
			{
				std::cout << "Compiled shader " << shader.getId() << std::endl;
				glAttachShader(programId_, shader.getId());
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
			glLinkProgram(programId_);

		isCompiled_ = !errorOccured;
	}

	return isCompiled_;
}