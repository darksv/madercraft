#pragma once

#include <map>

#include "GLTexture.hpp"

namespace mc
{

class TextureManager
{
protected:
	std::map<std::string, GLTexture*> loadedTextures_;

public:
	GLTexture* loadTextureFromFile(std::string filePath);
};

}