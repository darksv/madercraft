#pragma once

#include "BlockModel.hpp"

class BlockGrass : BlockModel
{
public:
	BlockGrass::BlockGrass(Texture* textureTop, Texture* textureBottom, Texture* textureSide, ShaderProgram* shader);
};