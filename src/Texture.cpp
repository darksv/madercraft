#include <iostream>

#include <GL/glew.h>

#include "Texture.hpp"

Texture::Texture(TextureType type, TexturePixelFormat pixelFormat, const std::vector<char>& data) :
	type_(type),
	pixelFormat_(pixelFormat),
	data_(data)
{
	size_t bytesPerPixel, pixelCount, dimension;
	if (pixelFormat == TexturePixelFormat::TEXTURE_RGB)
		bytesPerPixel = 3;

	pixelCount = data.size() / bytesPerPixel;

	dimension = std::sqrt(pixelCount);
	// detect square texture
	if (dimension * dimension == pixelCount)
		width_ = height_ = dimension;
}

Texture::Texture(TextureType type, TexturePixelFormat pixelFormat, size_t width, size_t height, const std::vector<char>& data) :
	type_(type),
	pixelFormat_(pixelFormat_),
	width_(width),
	height_(height),
	data_(data)
{
	
}


bool Texture::loadToGpu()
{
	glGenTextures(1, &textureId_);
	glBindTexture(GL_TEXTURE_2D, textureId_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data_.data());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	GLboolean isLoaded;
	glAreTexturesResident(1, &textureId_, &isLoaded);

	loaded_ = isLoaded;

	return isLoaded;
}

GLuint Texture::getId()
{
	if (!loaded_)
		loadToGpu();

	return textureId_;
}