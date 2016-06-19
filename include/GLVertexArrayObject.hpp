#pragma once

#include <GL/glew.h>
#include "GLBuffer.hpp"

class GLVertexArrayObject
{
public:
	GLVertexArrayObject(GLuint handle);
	~GLVertexArrayObject();

	void setAttrib(GLuint index, GLBuffer& buffer, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* offset) const noexcept;
	void unsetAttrib(GLuint index) const noexcept;
	
	void bind() const noexcept;
	void unbind() const noexcept;

private:
	GLuint handle_;
};

