#include <iostream>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GLVertexArrayObject.hpp"
#include "Mesh.hpp"

namespace mc
{

Mesh::Mesh(ShaderProgram* shaderProgram) :
	isLoaded_(false),
	shaderProgram_(shaderProgram)
{
}

void Mesh::load(GLContext& context)
{
	if (vertices_.size() == 0)
		return;

	if (isLoaded_)
		return;

	vao_ = context.getVertexArrayObject();
	vbo_ = context.getMutableBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(GLfloat) * vertices_.size() * 5, vertices_.data());
	vao_->setAttrib(0, *vbo_, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(0 * sizeof(GLfloat)));
	vao_->setAttrib(1, *vbo_, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));

	isLoaded_ = true;
}

void Mesh::draw(GLContext& context, std::vector<glm::vec3>& positions)
{
	if (!isLoaded_)
		load(context);

	const size_t instancesNum = positions.size();

	std::vector<glm::mat4> modelMatrices;
	modelMatrices.reserve(instancesNum);

	const auto identityMatrix = glm::mat4();
	for (size_t i = 0; i < instancesNum; ++i)
		modelMatrices.push_back(glm::translate(identityMatrix, positions[i]));

	GLint modelAttrib = glGetAttribLocation(shaderProgram_->getId(), "modelMatrix");

	vao_->bind();

	// create buffer for vector of model matrices for each instance
	auto modelMatricesBuffer = context.getMutableBuffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW, sizeof(glm::mat4) * instancesNum, modelMatrices.data());

	modelMatricesBuffer->bind();
	for (size_t i = 0; i < 4; ++i)
	{
		glEnableVertexAttribArray(modelAttrib + i);
		glVertexAttribPointer(modelAttrib + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), reinterpret_cast<GLvoid*>(4 * i * sizeof(GLfloat)));
		glVertexAttribDivisor(modelAttrib + i, 1);
	}
	modelMatricesBuffer->unbind();


	glUseProgram(shaderProgram_->getId());

	vbo_->bind();
	{
		glBindTexture(GL_TEXTURE_2D, textures_[0]->getId());
		glDrawArraysInstanced(GL_TRIANGLES, 6 * 0, 6 * 1, instancesNum);

		glBindTexture(GL_TEXTURE_2D, textures_[1]->getId());
		glDrawArraysInstanced(GL_TRIANGLES, 6 * 1, 6 * 1, instancesNum);

		glBindTexture(GL_TEXTURE_2D, textures_[2]->getId());
		glDrawArraysInstanced(GL_TRIANGLES, 6 * 2, 6 * 4, instancesNum);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	vbo_->bind();

	vao_->unbind();
}

ShaderProgram* Mesh::getShaderProgram() const
{
	return shaderProgram_;
}

}