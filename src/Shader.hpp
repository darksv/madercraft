#pragma once

#include <string>

#include <GL/GLew.h>

namespace mc
{

enum class ShaderType {
	VERTEX_SHADER,
	FRAGMENT_SHADER
};

class Shader
{
	friend class ShaderProgram;

protected:
	ShaderType type_;
	std::string filePath_;
	bool isFromFile_;

	GLuint shaderId_;
	bool isCompiled_;

public:
	Shader(ShaderType type, std::string filePath);
	Shader(const Shader& shader) = delete;

	GLuint getId() const;
	ShaderType getType() const;
};

}