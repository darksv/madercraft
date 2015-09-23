#include "shader.hpp"

static std::string getFileContent(std::string filePath)
{
	std::ifstream fileStream(filePath);
	std::string fileContent(
		(std::istreambuf_iterator<char>(fileStream)),
		(std::istreambuf_iterator<char>())
	);

	return fileContent;
}

GLuint loadAndCompileShader(GLenum shaderType, std::string shaderSource)
{
	GLuint shader = glCreateShader(shaderType);

	const GLchar * source = shaderSource.c_str();

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	return shader;
}


Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath) :
	mVertexShaderPath(vertexShaderPath),
	mFragmentShaderPath(fragmentShaderPath)
{
	mVertexShader = loadAndCompileShader(GL_VERTEX_SHADER, getFileContent(mVertexShaderPath));
	mFragmentShader = loadAndCompileShader(GL_FRAGMENT_SHADER, getFileContent(mFragmentShaderPath));
	
	mProgram = glCreateProgram();
	glAttachShader(mProgram, mVertexShader);
	glAttachShader(mProgram, mFragmentShader);
	glLinkProgram(mProgram);

	glDeleteShader(mVertexShader);
	glDeleteShader(mFragmentShader);
}


void Shader::use()
{
	glUseProgram(mProgram);
}

