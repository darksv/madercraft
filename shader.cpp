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
	vertexShaderPath_(vertexShaderPath),
	fragmentShaderPath_(fragmentShaderPath)
{
	vertexShader_ = loadAndCompileShader(GL_VERTEX_SHADER, getFileContent(vertexShaderPath_));
	fragmentShader_ = loadAndCompileShader(GL_FRAGMENT_SHADER, getFileContent(fragmentShaderPath_));
	
	program_ = glCreateProgram();
	glAttachShader(program_, vertexShader_);
	glAttachShader(program_, fragmentShader_);
	glLinkProgram(program_);

	glDeleteShader(vertexShader_);
	glDeleteShader(fragmentShader_);
}


void Shader::use()
{
	glUseProgram(program_);
}

