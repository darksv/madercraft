#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <GL/GLew.h>

class Shader {
protected:
	std::string mVertexShaderPath;
	std::string mFragmentShaderPath;
	GLuint mVertexShader;
	GLuint mFragmentShader;
	GLuint mProgram;

public:
	Shader(std::string vertexShaderPath, std::string fragmentShaderPath);

	GLuint getProgram() const { return mProgram; };
	void use();
};

#endif