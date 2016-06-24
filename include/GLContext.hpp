#pragma once

#include <memory>

#include <GL/glew.h>

#include "GLBuffer.hpp"
#include "GLVertexArrayObject.hpp"
#include "GLShaderProgram.hpp"

class GLContext
{
public:
	GLContext();
	~GLContext();

	void depthTestEnabled(bool enabled) const noexcept;
	void faceCullingEnabled(bool enabled) const noexcept;
	void setCullingMode(GLenum cullFace, GLenum frontFace) const noexcept;

	std::unique_ptr<GLBuffer> getMutableBuffer(GLenum target, GLenum usage, GLsizei size, void* data) const noexcept;
	std::unique_ptr<GLVertexArrayObject> getVertexArrayObject() const noexcept;
	std::unique_ptr<GLShaderProgram> getShaderProgram() const noexcept;
};

