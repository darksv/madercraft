#include "texture.hpp"

std::vector<char> getTexture(std::string filePath)
{
	std::ifstream fileStream(filePath, std::ios::binary);
	return std::vector<char>(
		(std::istreambuf_iterator<char>(fileStream)),
		(std::istreambuf_iterator<char>())
	);
}

Texture::Texture(std::string filePath)
{
	imageData_ = getTexture(filePath);

	glGenTextures(1, &textureId_);
	glBindTexture(GL_TEXTURE_2D, textureId_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData_.data());
	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, textureId_);
}

void Texture::unbind()
{
	glBindTextureEXT(GL_TEXTURE_2D, 0);
}