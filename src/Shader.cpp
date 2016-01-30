#include <iostream>

#include "helpers.hpp"
#include "Shader.hpp"

Shader::Shader(ShaderType type, std::string filePath) :
	type_(type),
	filePath_(filePath),
	isCompiled_(false)
{
	auto shaderSource = getFileContent(filePath);
	source_ = std::string(shaderSource.begin(), shaderSource.end());
}

GLuint Shader::getId()
{
	return shaderId_;
}

bool Shader::compile()
{
	if (isCompiled_)
		return true;

	GLenum shaderType;
	switch (type_)
	{
	case ShaderType::FRAGMENT_SHADER:
		shaderType = GL_FRAGMENT_SHADER;
		break;
	case ShaderType::VERTEX_SHADER:
		shaderType = GL_VERTEX_SHADER;
		break;
	}

	shaderId_ = glCreateShader(shaderType);

	const GLchar* source = source_.c_str();
	GLint length = source_.size();

	glShaderSource(shaderId_, 1, &source, &length);
	glCompileShader(shaderId_);

	GLint success = 0;
	glGetShaderiv(shaderId_, GL_COMPILE_STATUS, &success);

	if (success)
		isCompiled_ = true;

	return success;
}

