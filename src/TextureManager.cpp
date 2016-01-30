#include "helpers.hpp"
#include "TextureManager.hpp"

Texture * TextureManager::loadTexture(std::string filePath)
{
	for (auto pair : loadedTextures_)
		if (pair.first == filePath)
			return pair.second;
		
	Texture * texture = new Texture(TextureType::TEXTURE_2D, TexturePixelFormat::TEXTURE_RGB, getFileContent(filePath));

	loadedTextures_[filePath] = texture;

	return texture;
}
