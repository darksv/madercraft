#pragma once
#include <GL/glew.h>

class GLContext
{
public:
	GLContext();
	~GLContext();

	void depthTestEnabled(bool enabled) noexcept;
	void faceCullingEnabled(bool enabled) noexcept;
	void setCullingMode(GLenum cullFace, GLenum frontFace) noexcept;
};

