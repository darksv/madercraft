#pragma once

#include <GL/glew.h>

class GLBuffer
{
public:
	GLBuffer(GLenum type, GLuint handle, GLsizei size);
	~GLBuffer();

	GLuint getHandle() const noexcept { return handle_; }
	void bind() const noexcept;
	void unbind() const noexcept;

private:
	GLenum target_;
	GLuint handle_;
	GLsizei size_;
};

