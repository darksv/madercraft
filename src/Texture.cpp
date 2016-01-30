#include <iostream>

#include <GL/glew.h>

#include "Texture.hpp"

Texture::Texture(TextureType type, TextureFormat format, const std::vector<char>& data)
	: type_(type), format_(format), data_(data)
{
	if (format == TextureFormat::TEXTURE_RGB)
	{
		size_t dimension = std::sqrt(data.size() / 3);

		if (dimension * dimension == data.size() / 3)
		{
			width_ = height_ = dimension;
		}
	}
}

Texture::Texture(TextureType type, TextureFormat format, size_t width, size_t height, const std::vector<char>& data)
	: type_(type), format_(format), width_(width), height_(height), data_(data)
{
	
}


bool Texture::loadToGpu()
{
	glGenTextures(1, &textureId_);
	glBindTexture(GL_TEXTURE_2D, textureId_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data_.data());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	loaded_ = true;

	return true;
}

GLuint Texture::getId()
{
	if (!loaded_)
		loaded_ = loadToGpu();

	return textureId_;
}