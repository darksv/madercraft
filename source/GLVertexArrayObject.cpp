#include "GLVertexArrayObject.hpp"

GLVertexArrayObject::GLVertexArrayObject(GLuint handle) :
	handle_(handle)
{
}

GLVertexArrayObject::~GLVertexArrayObject()
{
	glDeleteVertexArrays(1, &handle_);
}

void GLVertexArrayObject::bind() const noexcept
{
	glBindVertexArray(handle_);
}

void GLVertexArrayObject::unbind() const noexcept
{
	glBindVertexArray(0);
}
