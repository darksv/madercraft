#pragma once

#include <array>

#include "GLShaderProgram.hpp"
#include "Mesh.hpp"
#include "GLTexture.hpp"

namespace mc
{

class BlockModel
{
public:
	BlockModel(Mesh* mesh, GLTexture* textureTop, GLTexture* textureBottom, GLTexture* textureSide, GLShaderProgram* shaderProgram);
	BlockModel(const BlockModel&) = delete;

	GLShaderProgram* getShaderProgram() { return shaderProgram_; }
	Mesh* getMesh() { return mesh_; }

private:
	Mesh* mesh_;
	GLShaderProgram* shaderProgram_;
	std::vector<GLTexture*> textures_;
};

}