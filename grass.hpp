#pragma once

#include "block.hpp"

class BlockGrass : BlockModel
{
public:
	BlockGrass::BlockGrass(Texture* textureTop, Texture* textureBottom, Texture* textureSide, Shader* shader);
};