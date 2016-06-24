#pragma once

#include <list>

#include <GL/glew.h>

#include <glm/mat4x4.hpp>


enum class ShaderType {
	Vertex,
	Fragment
};

class Shader
{
public:
	Shader(ShaderType type, std::string filePath);
	Shader(const Shader& shader) = delete;

	ShaderType getType() const;

private:
	ShaderType type_;
	std::string filePath_;
	bool isFromFile_;

	GLuint handle_;
	bool isCompiled_;

	friend class GLShaderProgram;
};

class GLShaderProgram
{
public:
	GLShaderProgram(GLuint handle);
	GLShaderProgram(const GLShaderProgram& shaderProgram) = delete;

	void setUniform(const GLchar* name, const GLfloat f);
	void setUniform(const GLchar* name, const glm::mat4& mat);

	void addShaderFromFile(ShaderType type, std::string filePath);
	bool compileShader(Shader& shader);
	bool compile();
	void use();

private:
	std::list<Shader> shaders_;
	GLuint handle_;
	bool isCompiled_;
};
