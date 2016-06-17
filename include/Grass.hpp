#pragma once

#include "BlockModel.hpp"

namespace mc
{

class BlockGrass : BlockModel
{
public:
	BlockGrass(Texture* textureTop, Texture* textureBottom, Texture* textureSide, ShaderProgram* shader);
};

}