#include <string>
#include "block.hpp"

BlockModel::BlockModel(Texture* textureTop, Texture* textureBottom, Texture* textureSide, Shader* shader) :
	textureTop_(textureTop),
	textureBottom_(textureBottom),
	textureSide_(textureSide),
	shader_(shader)
{
	glGenVertexArrays(1, &vao_);
	glGenBuffers(1, &vbo_);

	glBindVertexArray(vao_);

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

BlockGrass::BlockGrass()
	: BlockModel(new Texture("textures\\cube_top.raw"), new Texture("textures\\cube_bottom.raw"), new Texture("textures\\cube_side.raw"), new Shader("shaders\\cube.vs", "shaders\\cube.frag"))
{

}
