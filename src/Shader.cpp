#include <iostream>

#include "Shader.hpp"

Shader::Shader(ShaderType type, std::string filePath) :
	type_(type),
	filePath_(filePath),
	isFromFile_(true),
	isCompiled_(false)
{
	
}

GLuint Shader::getId() const
{
	return shaderId_;
}

ShaderType Shader::getType() const
{
	return type_;
}

