#pragma once

#include <array>

#include <GL/glew.h>

#include "Mesh.hpp"
#include "GLShaderProgram.hpp"
#include "Texture.hpp"

namespace mc
{

class BlockModel
{
public:
	BlockModel(Mesh* mesh, Texture* textureTop, Texture* textureBottom, Texture* textureSide, GLShaderProgram* shaderProgram);
	BlockModel(const BlockModel&) = delete;

	GLShaderProgram* getShaderProgram() { return shaderProgram_; }
	Mesh* getMesh() { return mesh_; }

private:
	Mesh* mesh_;
	GLShaderProgram* shaderProgram_;
	std::vector<Texture*> textures_;
};

}