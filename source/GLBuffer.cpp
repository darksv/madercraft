#include "GLBuffer.hpp"

GLBuffer::GLBuffer(GLenum target, GLuint handle, GLsizei size) :
	target_(target),
	handle_(handle),
	size_(size)
{
}

GLBuffer::~GLBuffer()
{
	glDeleteBuffers(1, &handle_);
}

void GLBuffer::bind() const noexcept
{
	glBindBuffer(target_, handle_);
}

void GLBuffer::unbind() const noexcept
{
	glBindBuffer(target_, 0);
}
