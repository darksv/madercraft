#pragma once

#include "BlockModel.hpp"

namespace mc
{

class BlockDirt : BlockModel
{
public:
	BlockDirt(Texture* textureTop, Texture* textureBottom, Texture* textureSide, ShaderProgram* shader);
};

}