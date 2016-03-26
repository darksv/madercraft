#include <chrono>
#include <iostream>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BlockModel.hpp"

BlockModel::BlockModel(Texture* textureTop, Texture* textureBottom, Texture* textureSide, ShaderProgram* shaderProgram) :
	Mesh(shaderProgram)
{
	vertices_.reserve(180);

	// Bottom face
	vertices_.push_back({ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f} }); // BL
	vertices_.push_back({ { 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f} }); // BR
	vertices_.push_back({ { 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} }); // TR
	vertices_.push_back({ { 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} }); // TR
	vertices_.push_back({ {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f} }); // TL
	vertices_.push_back({ {-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f} }); // BL

	// Top face
	vertices_.push_back({ {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} }); // BL
	vertices_.push_back({ { 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f} }); // TR
	vertices_.push_back({ { 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} }); // BR
	vertices_.push_back({ { 0.5f,  0.5f,  0.5f}, {1.0f, 1.0f} }); // TR
	vertices_.push_back({ {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} }); // BL
	vertices_.push_back({ {-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f} }); // TL

	// Front face
	vertices_.push_back({ {-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} }); // TR
	vertices_.push_back({ {-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} }); // BL
	vertices_.push_back({ {-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} }); // TL      
	vertices_.push_back({ {-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} }); // BL
	vertices_.push_back({ {-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} }); // TR
	vertices_.push_back({ {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} }); // BR

	// Back face
	vertices_.push_back({ { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} }); // TL
	vertices_.push_back({ { 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} }); // TR     
	vertices_.push_back({ { 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} }); // BR
	vertices_.push_back({ { 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} }); // BR
	vertices_.push_back({ { 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} }); // BL
	vertices_.push_back({ { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} }); // TL

	// Right face
	vertices_.push_back({ {-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} }); // TR
	vertices_.push_back({ { 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} }); // BL
	vertices_.push_back({ { 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f} }); // TL
	vertices_.push_back({ { 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f} }); // BL
	vertices_.push_back({ {-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f} }); // TR
	vertices_.push_back({ {-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f} }); // BR

	// Left face
	vertices_.push_back({ {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f} }); // TL
	vertices_.push_back({ { 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f} }); // TR
	vertices_.push_back({ { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} }); // BR
	vertices_.push_back({ { 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f} }); // BR
	vertices_.push_back({ {-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f} }); // BL
	vertices_.push_back({ {-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f} }); // TL

	textures_.push_back(textureBottom);
	textures_.push_back(textureTop);
	textures_.push_back(textureSide);
}

