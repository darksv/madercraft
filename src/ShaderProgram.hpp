#pragma once

#include <vector>

#include "Shader.hpp"

class ShaderProgram
{
protected:
	std::vector <Shader*> shaders_;
	GLuint programId_;
	bool isCompiled_;

public:
	ShaderProgram();
	ShaderProgram(const ShaderProgram& shaderProgram) = delete;

	GLuint getId();
	GLint getUniform(const GLchar* name);

	void addShader(Shader* shader);
	bool compile();
};