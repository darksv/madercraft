#include <iostream>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLVertexArrayObject.hpp"
#include "Mesh.hpp"

namespace mc
{

Mesh::Mesh(std::vector<Vertice> vertices) :
	vertices_(vertices)
{
	
}

void Mesh::load(GLContext& context)
{
	if (vertices_.size() == 0)
		return;

	vao_ = context.getVertexArrayObject();
	vbo_ = context.getMutableBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(Vertice) * vertices_.size(), vertices_.data());
	vao_->setAttrib(0, *vbo_, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0 * sizeof(GLfloat)));
	vao_->setAttrib(1, *vbo_, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));

	isLoaded_ = true;
}

void Mesh::drawMultiple(GLContext& context, std::vector<glm::vec3>& positions)
{
	if (!isLoaded_)
		load(context);

	const size_t instancesNum = positions.size();

	std::vector<glm::mat4> modelMatrices;
	modelMatrices.reserve(instancesNum);

	const auto identityMatrix = glm::mat4();
	for (size_t i = 0; i < instancesNum; ++i)
		modelMatrices.push_back(glm::translate(identityMatrix, positions[i]));

	vao_->bind();
	{
		// create buffer for vector of model matrices for each instance
		auto modelMatricesBuffer = context.getMutableBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(glm::mat4) * instancesNum, modelMatrices.data());

		modelMatricesBuffer->bind();
		for (size_t i = 0; i < 4; ++i)
		{
			vao_->setAttrib(2 + i, *modelMatricesBuffer, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<GLvoid*>(4 * i * sizeof(GLfloat)));
			glVertexAttribDivisor(2 + i, 1);
		}
		modelMatricesBuffer->unbind();

		vbo_->bind();
		glDrawArraysInstanced(GL_TRIANGLES, 0, vertices_.size(), instancesNum);
		vbo_->unbind();
	}
	vao_->unbind();
}

}