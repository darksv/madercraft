#pragma once

#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "ShaderProgram.hpp"
#include "Texture.hpp"

namespace mc
{

using Vertice = std::pair<glm::vec3, glm::vec2>;

class Mesh
{
protected:
	std::vector<Vertice> vertices_;
	std::vector<Texture*> textures_;
	ShaderProgram* shaderProgram_;
	GLuint vao_, vbo_;
	bool isLoaded_;

	virtual void load();

public:
	Mesh(ShaderProgram* shaderProgram);
	ShaderProgram* getShaderProgram() const;

	void draw(std::vector<glm::vec3>& positions);
};

}