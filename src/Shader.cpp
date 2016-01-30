#include <iostream>

#include "Shader.hpp"

Shader::Shader(ShaderType type, std::string filePath) :
	type_(type),
	filePath_(filePath),
	isCompiled_(false)
{
	
}

GLuint Shader::getId()
{
	return shaderId_;
}

ShaderType Shader::getType()
{
	return type_;
}

