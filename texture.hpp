#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <GL/glew.h>

class Texture {
protected:
	GLuint textureId_;
	std::vector<char> imageData_;
public:
	Texture(std::string filePath);

	void bind();
	void unbind();
};

#endif