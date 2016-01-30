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
		programId_ = glCreateProgram();

		for (Shader* shader : shaders_)
			if (shader->compile())
				glAttachShader(programId_, shader->getId());
		

		glLinkProgram(programId_);

		isCompiled_ = true;
	}

	return isCompiled_;
}