#pragma once

#include <string>

#include <GL/GLew.h>

enum class ShaderType {
	VERTEX_SHADER,
	FRAGMENT_SHADER
};

class Shader
{
protected:
	ShaderType type_;
	std::string filePath_;
	std::string source_;
	GLuint shaderId_;
	bool isCompiled_;

public:
	Shader(ShaderType type, std::string filePath);
	Shader(const Shader& shader) = delete;

	GLuint getId();
	bool compile();
};