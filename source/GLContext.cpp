#include "GLContext.hpp"
#include <GL/glew.h>
#include <glm/mat4x2.hpp>


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

std::unique_ptr<GLBuffer> GLContext::getMutableBuffer(GLenum target, GLenum usage, GLsizei size, void* data) const noexcept
{
	GLuint handle;
	glGenBuffers(1, &handle);
	glBindBuffer(target, handle);
	glBufferData(target, size, data, usage);
	glBindBuffer(target, 0);

	return std::make_unique<GLBuffer>(target, handle, size);
}

std::unique_ptr<GLVertexArrayObject> GLContext::getVertexArrayObject() const noexcept
{
	GLuint handle;
	glGenVertexArrays(1, &handle);

	return std::make_unique<GLVertexArrayObject>(handle);
}

std::unique_ptr<GLShaderProgram> GLContext::getShaderProgram() const noexcept
{
	return std::make_unique<GLShaderProgram>(glCreateProgram());
}
