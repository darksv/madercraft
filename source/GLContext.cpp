#include "GLContext.hpp"
#include <GL/glew.h>


GLContext::GLContext()
{
}


GLContext::~GLContext()
{
}

void GLContext::depthTestEnabled(bool enabled) noexcept
{
	if (enabled)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void GLContext::faceCullingEnabled(bool enabled) noexcept
{
	if (enabled)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void GLContext::setCullingMode(GLenum cullFace, GLenum frontFace) noexcept
{
	glCullFace(cullFace);
	glFrontFace(frontFace);
}
