#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include <string>
#include <vector>
#include <fstream>
#include <GL/glew.h>

class Texture {
protected:
	GLuint mTexture;
	std::vector<char> mImage;
public:
	Texture(std::string filePath);

	void bind();
	void unbind();
};

#endif