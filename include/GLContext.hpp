#pragma once

#include <memory>
#include <GL/glew.h>
#include "GLVertexArrayObject.hpp"

class GLContext
{
public:
	GLContext();
	~GLContext();

	void depthTestEnabled(bool enabled) const noexcept;
	void faceCullingEnabled(bool enabled) const noexcept;
	void setCullingMode(GLenum cullFace, GLenum frontFace) const noexcept;

	std::unique_ptr<GLVertexArrayObject> getVertexArrayObject() const noexcept;
};

