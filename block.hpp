#pragma once

#include <array>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.hpp"
#include "Texture.hpp"

struct BlockModel
{
protected:
	std::array<GLfloat, 180> vertices_ = {
		// Bottom face
		-0.5f, -0.5f,  -0.5f, 0.0f, 0.0f, // BL
		 0.5f, -0.5f,  -0.5f, 1.0f, 0.0f, // BR  
		 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, // TR
		 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, // TR
		-0.5f,  0.5f,  -0.5f, 0.0f, 1.0f, // TL
		-0.5f, -0.5f,  -0.5f, 0.0f, 0.0f, // BL

		// Top face
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // BL
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // TR
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // BR
		 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, // TR
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // BL
		-0.5f,  0.5f,  0.5f, 0.0f, 1.0f, // TL

		// Front face
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // TR
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // BL
		-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // TL      
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // BL
		-0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // TR
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // BR

		// Back face
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // TL
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // TR     
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // BR
		 0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // BR
		 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // BL
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // TL

		// Right face
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // TR
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // BL
		 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, // TL
		 0.5f, -0.5f,  0.5f, 1.0f, 0.0f, // BL
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // TR
		-0.5f, -0.5f,  0.5f, 0.0f, 0.0f, // BR

		// Left face
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f, // TL
		 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, // TR
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // BR
		 0.5f,  0.5f,  0.5f, 1.0f, 0.0f, // BR
		-0.5f,  0.5f,  0.5f, 0.0f, 0.0f, // BL
		-0.5f,  0.5f, -0.5f, 0.0f, 1.0f  // TL
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
	void draw(std::vector<glm::vec3>& positions);
};