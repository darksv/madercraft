#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <GL/GLew.h>

class Shader {
protected:
	std::string vertexShaderPath_;
	std::string fragmentShaderPath_;
	GLuint vertexShader_;
	GLuint fragmentShader_;
	GLuint program_;

public:
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);

	GLuint getProgram() const { return program_; };
	void use();

	GLint getUniform(const GLchar* name);
};

#endif