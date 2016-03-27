#pragma once

#include <map>

#include "Texture.hpp"

namespace mc
{

class TextureManager
{
protected:
	std::map<std::string, Texture*> loadedTextures_;

public:
	Texture* loadTextureFromFile(std::string filePath);
};

}