#include "Dirt.hpp"

namespace mc
{

BlockDirt::BlockDirt(Texture* textureTop, Texture* textureBottom, Texture* textureSide, ShaderProgram* shaderProgram) :
	BlockModel(textureTop, textureBottom, textureSide, shaderProgram)
{

}

}