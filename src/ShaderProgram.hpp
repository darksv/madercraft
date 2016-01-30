#pragma once

#include <list>
#include <vector>

#include "Shader.hpp"

class ShaderProgram
{
protected:
	//std::vector <Shader*> shaders_;
	std::list<Shader> shaders_;
	GLuint programId_;
	bool isCompiled_;

public:
	ShaderProgram();
	ShaderProgram(const ShaderProgram& shaderProgram) = delete;

	GLuint getId();
	GLint getUniform(const GLchar* name);

	void addShaderFromFile(ShaderType type, std::string filePath);
	bool compileShader(Shader& shader);
	bool compile();
};