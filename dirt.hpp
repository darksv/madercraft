#pragma once

#include "Block.hpp"

class BlockDirt : BlockModel
{
public:
	BlockDirt::BlockDirt(Texture* textureTop, Texture* textureBottom, Texture* textureSide, Shader* shader);
};