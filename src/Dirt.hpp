#pragma once

#include "BlockModel.hpp"

class BlockDirt : BlockModel
{
public:
	BlockDirt::BlockDirt(Texture* textureTop, Texture* textureBottom, Texture* textureSide, ShaderProgram* shader);
};