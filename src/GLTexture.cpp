#include <GL/glew.h>

#include "GLTexture.hpp"

GLTexture::GLTexture(GLenum target, GLuint handle, GLsizei width, GLsizei height) :
	target_(target),
	handle_(handle),
	width_(width),
	height_(height)
{
}

void GLTexture::bind() const noexcept
{
	glBindTexture(target_, handle_);
}

void GLTexture::unbind() const noexcept
{
	glBindTexture(target_, 0);
}