#include "GLVertexArrayObject.hpp"

GLVertexArrayObject::GLVertexArrayObject(GLuint handle) :
	handle_(handle)
{
}

GLVertexArrayObject::~GLVertexArrayObject()
{
	glDeleteVertexArrays(1, &handle_);
}

void GLVertexArrayObject::setAttrib(GLuint index, GLBuffer& buffer, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) const noexcept
{
	bind();
	glEnableVertexAttribArray(index);
	buffer.bind();
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

void GLVertexArrayObject::unsetAttrib(GLuint index) const noexcept
{
	bind();
	glDisableVertexAttribArray(index);
}

void GLVertexArrayObject::bind() const noexcept
{
	glBindVertexArray(handle_);
}

void GLVertexArrayObject::unbind() const noexcept
{
	glBindVertexArray(0);
}
