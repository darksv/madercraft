#include "helpers.hpp"
#include "TextureManager.hpp"

namespace mc
{

GLTexture* TextureManager::loadTextureFromFile(std::string filePath)
{
	for (auto pair : loadedTextures_)
		if (pair.first == filePath)
			return pair.second;

	GLTexture* texture = new GLTexture(TextureType::TEXTURE_2D, TexturePixelFormat::TEXTURE_RGB, getFileContent(filePath));

	loadedTextures_[filePath] = texture;

	return texture;
}

}