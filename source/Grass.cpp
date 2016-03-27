#include "Grass.hpp"

namespace mc
{

BlockGrass::BlockGrass(Texture* textureTop, Texture* textureBottom, Texture* textureSide, ShaderProgram* shaderProgram) :
	BlockModel(textureTop, textureBottom, textureSide, shaderProgram)
{

}

}