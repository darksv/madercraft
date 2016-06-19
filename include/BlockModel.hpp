#pragma once

#include <array>

#include <GL/glew.h>

#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

namespace mc
{

class BlockModel
{
public:
	BlockModel(Mesh* mesh, Texture* textureTop, Texture* textureBottom, Texture* textureSide, ShaderProgram* shaderProgram);
	BlockModel(const BlockModel&) = delete;

	ShaderProgram* getShaderProgram() { return shaderProgram_; }
	Mesh* getMesh() { return mesh_; }

private:
	Mesh* mesh_;
	ShaderProgram* shaderProgram_;
	std::vector<Texture*> textures_;
};

}