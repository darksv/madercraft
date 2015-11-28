#include "texture.hpp"
#include "helpers.hpp"

Texture::Texture(std::string filePath)
{
	imageData_ = getFileContent(filePath);

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