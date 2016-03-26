#pragma once

#include <array>

#include <GL/glew.h>

#include "Mesh.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

class BlockModel : public Mesh
{
public:
	BlockModel(Texture* textureTop, Texture* textureBottom, Texture* textureSide, ShaderProgram* shaderProgram);
	BlockModel(const BlockModel&) = delete;
};