#include <iostream>

#include "ShaderProgram.hpp"

GLuint ShaderProgram::getId()
{
	return programId_;
}

GLint ShaderProgram::getUniform(const GLchar* name)
{
	return glGetUniformLocation(programId_, name);
}

void ShaderProgram::addShader(Shader* shader)
{
	shaders_.push_back(shader);
}

bool ShaderProgram::compile()
{
	if (!isCompiled_)
	{
		bool errorOccured = false;

		programId_ = glCreateProgram();

		for (Shader* shader : shaders_)
		{
			if (shader->compile())
			{
				std::cout << "Compiled shader " << shader->getId() << std::endl;
				glAttachShader(programId_, shader->getId());
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