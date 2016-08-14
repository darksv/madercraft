#pragma once

#include <GL/glew.h>

class GLTexture
{
public:
	GLTexture(GLenum target, GLuint handle, GLsizei width, GLsizei height);
	GLTexture(const GLTexture& texture) = delete;

	void bind() const noexcept;
	void unbind() const noexcept;

private:
	GLenum target_;
	GLuint handle_;
	GLsizei width_;
	GLsizei height_;
};