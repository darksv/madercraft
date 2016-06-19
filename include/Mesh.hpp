#pragma once

#include <vector>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "GLContext.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

namespace mc
{

using Vertice = std::pair<glm::vec3, glm::vec2>;

class Mesh
{
protected:
	std::unique_ptr<GLVertexArrayObject> vao_;
	std::unique_ptr<GLBuffer> vbo_;

	std::vector<Vertice> vertices_;
	bool isLoaded_;

	virtual void load(GLContext& context);

public:
	Mesh(std::vector<Vertice> vertices);

	void drawMultiple(GLContext& context, std::vector<glm::vec3>& positions);
};

}