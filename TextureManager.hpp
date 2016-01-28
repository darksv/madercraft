#pragma once

#include <map>

#include "Texture.hpp"

class TextureManager
{
protected:
	std::map<std::string, Texture*> loadedTextures_;

public:
	Texture * loadTexture(std::string filePath);
};