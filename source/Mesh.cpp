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
	vbo_(0),
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
	vao_->bind();

	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices_.size() * 5, vertices_.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	vao_->unbind();

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

	GLuint modelMatricesBuffer;
	GLint modelAttrib = glGetAttribLocation(shaderProgram_->getId(), "modelMatrix");

	vao_->bind();

	// create buffer for vector of model matrices for each instance
	glGenBuffers(1, &modelMatricesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, modelMatricesBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instancesNum, modelMatrices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glEnableVertexAttribArray(modelAttrib + 0);
	glEnableVertexAttribArray(modelAttrib + 1);
	glEnableVertexAttribArray(modelAttrib + 2);
	glEnableVertexAttribArray(modelAttrib + 3);

	glBindBuffer(GL_ARRAY_BUFFER, modelMatricesBuffer);
	glVertexAttribPointer(modelAttrib + 0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(0 * sizeof(GLfloat)));
	glVertexAttribPointer(modelAttrib + 1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(4 * sizeof(GLfloat)));
	glVertexAttribPointer(modelAttrib + 2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(8 * sizeof(GLfloat)));
	glVertexAttribPointer(modelAttrib + 3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(12 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(modelAttrib + 0, 1);
	glVertexAttribDivisor(modelAttrib + 1, 1);
	glVertexAttribDivisor(modelAttrib + 2, 1);
	glVertexAttribDivisor(modelAttrib + 3, 1);

	glUseProgram(shaderProgram_->getId());

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	{
		glBindTexture(GL_TEXTURE_2D, textures_[0]->getId());
		glDrawArraysInstanced(GL_TRIANGLES, 6 * 0, 6 * 1, instancesNum);

		glBindTexture(GL_TEXTURE_2D, textures_[1]->getId());
		glDrawArraysInstanced(GL_TRIANGLES, 6 * 1, 6 * 1, instancesNum);

		glBindTexture(GL_TEXTURE_2D, textures_[2]->getId());
		glDrawArraysInstanced(GL_TRIANGLES, 6 * 2, 6 * 4, instancesNum);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	vao_->unbind();

	glDeleteBuffers(1, &modelMatricesBuffer);
}

ShaderProgram* Mesh::getShaderProgram() const
{
	return shaderProgram_;
}

}