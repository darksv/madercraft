#pragma once

#include <GL/glew.h>

class GLVertexArrayObject
{
public:
	GLVertexArrayObject(GLuint handle);
	~GLVertexArrayObject();

	void bind() const noexcept;
	void unbind() const noexcept;

private:
	GLuint handle_;
};

