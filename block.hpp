#ifndef _BLOCK_H
#define _BLOCK_H

#include <string>
#include <array>
#include <GL\glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "texture.hpp"
#include "shader.hpp"

struct BlockModel
{
protected:
	std::array<GLfloat, 180> vertices_ = {
		// top
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

		// bottom
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

		// sides
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 1.0f, 1.0f,

		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 1.0f,

		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 1.0f, 1.0f
	};

	Texture* textureTop_;
	Texture* textureBottom_;
	Texture* textureSide_;

	Shader* shader_;

	GLuint vao_, vbo_;

public:
	BlockModel(Texture* textureTop, Texture* textureBottom, Texture* textureSide, Shader* shader);
	BlockModel(const BlockModel&) = delete;

	Shader* getShader();
	void draw(glm::vec3& position);
};


struct BlockGrass : BlockModel
{
public:
	BlockGrass();
};

#endif