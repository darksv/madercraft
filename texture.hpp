#pragma once

#include <string>
#include <vector>

#include <GL/glew.h>

class Texture
{
protected:
	GLuint textureId_;
	std::vector<char> imageData_;

public:
	Texture(std::string filePath);

	GLuint getId();
};