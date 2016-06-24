#include "BlockModel.hpp"

namespace mc
{

BlockModel::BlockModel(Mesh* mesh, Texture* textureTop, Texture* textureBottom, Texture* textureSide, GLShaderProgram* shaderProgram) :
	mesh_(mesh),
	shaderProgram_(shaderProgram)
{
	textures_.push_back(textureBottom);
	textures_.push_back(textureTop);
	textures_.push_back(textureSide);
}

}