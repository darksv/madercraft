#include "GLContext.hpp"
#include <GL/glew.h>


GLContext::GLContext()
{
}


GLContext::~GLContext()
{
}

void GLContext::depthTestEnabled(bool enabled) const noexcept
{
	if (enabled)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);
}

void GLContext::faceCullingEnabled(bool enabled) const noexcept
{
	if (enabled)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}

void GLContext::setCullingMode(GLenum cullFace, GLenum frontFace) const noexcept
{
	glCullFace(cullFace);
	glFrontFace(frontFace);
}

std::unique_ptr<GLVertexArrayObject> GLContext::getVertexArrayObject() const noexcept
{
	GLuint handle;
	glGenVertexArrays(1, &handle);

	return std::make_unique<GLVertexArrayObject>(handle);
}
