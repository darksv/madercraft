#include <string>
#include "block.hpp"

BlockModel::BlockModel(Texture* textureTop, Texture* textureBottom, Texture* textureSide, Shader* shader) :
	textureTop_(textureTop),
	textureBottom_(textureBottom),
	textureSide_(textureSide),
	shader_(shader)
{
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertices_.size(), vertices_.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

Shader* BlockModel::getShader()
{
	return shader_;
}

void BlockModel::draw(glm::vec3& position)
{
	shader_->use();

	glm::mat4 model;
	model = glm::translate(model, position);

	glUniformMatrix4fv(shader_->getUniform("model"), 1, GL_FALSE, glm::value_ptr(model));

	glBindVertexArray(vao_);

	textureTop_->bind();
	glDrawArrays(GL_TRIANGLES, 6 * 0, 6 * 1);

	textureSide_->bind();
	glDrawArrays(GL_TRIANGLES, 6 * 2, 6 * 4);

	textureBottom_->bind();
	glDrawArrays(GL_TRIANGLES, 6 * 1, 6 * 1);

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);
}

void BlockModel::draw(std::vector<glm::vec3>& positions)
{
	shader_->use();

	std::vector<glm::mat4> modelMatrices;
	modelMatrices.reserve(positions.size());

	for (auto position : positions)
	{
		modelMatrices.push_back(glm::translate(glm::mat4(), position));
	}

	GLuint modelMatricesBuffer;
	GLint modelAttrib = glGetAttribLocation(shader_->getProgram(), "model");

	glBindVertexArray(vao_);

	// create buffer for vector of model matrices for each instance
	glGenBuffers(1, &modelMatricesBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, modelMatricesBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * modelMatrices.size(), modelMatrices.data(), GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(modelAttrib + 0);
	glEnableVertexAttribArray(modelAttrib + 1);
	glEnableVertexAttribArray(modelAttrib + 2);
	glEnableVertexAttribArray(modelAttrib + 3);
	
	glBindBuffer(GL_ARRAY_BUFFER, modelMatricesBuffer);
	glVertexAttribPointer(modelAttrib + 0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)( 0 * sizeof(GLfloat)));
	glVertexAttribPointer(modelAttrib + 1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)( 4 * sizeof(GLfloat)));
	glVertexAttribPointer(modelAttrib + 2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)( 8 * sizeof(GLfloat)));
	glVertexAttribPointer(modelAttrib + 3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (GLvoid*)(12 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(modelAttrib + 0, 1);
	glVertexAttribDivisor(modelAttrib + 1, 1);
	glVertexAttribDivisor(modelAttrib + 2, 1);
	glVertexAttribDivisor(modelAttrib + 3, 1);

	glBindBuffer(GL_ARRAY_BUFFER, vbo_);

	textureTop_->bind();
	glDrawArraysInstanced(GL_TRIANGLES, 6 * 0, 6 * 1, modelMatrices.size());

	textureSide_->bind();
	glDrawArraysInstanced(GL_TRIANGLES, 6 * 2, 6 * 4, modelMatrices.size());

	textureBottom_->bind();
	glDrawArraysInstanced(GL_TRIANGLES, 6 * 1, 6 * 1, modelMatrices.size());

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	glBindVertexArray(0);

	glDeleteBuffers(1, &modelMatricesBuffer);
}

BlockGrass::BlockGrass()
	: BlockModel(new Texture("textures\\cube_top.raw"), new Texture("textures\\cube_bottom.raw"), new Texture("textures\\cube_side.raw"), new Shader("shaders\\cube.vs", "shaders\\cube.frag"))
{

}
