#include <chrono>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BlockModel.hpp"

namespace mc
{

BlockModel::BlockModel(Mesh* mesh, Texture* textureTop, Texture* textureBottom, Texture* textureSide, ShaderProgram* shaderProgram) :
	mesh_(mesh),
	shaderProgram_(shaderProgram)
{
	textures_.push_back(textureBottom);
	textures_.push_back(textureTop);
	textures_.push_back(textureSide);
}

}